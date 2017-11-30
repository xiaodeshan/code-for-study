## pbft������������

���ڵ���vpʱ��server���� -> GetEngine����engine.consenterΪobcBatch��obcBatch��һ����ԱexternalEventReceiverʵ����RecvMsg
������
id:��getValidatorID�ɵ�  ��vpX..id��ΪX��

���յ���Ϣʱ����noops��Ϣ����һ����������externalEventReceiver.RecvMsg:
``` go
// RecvMsg is called by the stack when a new message is received
func (eer *externalEventReceiver) RecvMsg(ocMsg *pb.Message, senderHandle *pb.PeerID) error {
	eer.manager.Queue() <- batchMessageEvent{
		msg:    ocMsg,
		sender: senderHandle,
	}
	return nil
}
```

����externalEventReceiver���õ�Receiver��obcbatch,�������������¼�����obcbatch.ProcessEvent����obcbatch.ProcessEventת
����obcbatch.processMessage��Ȼ�����op.submitToLeader(req)

submitToLeader���¸�����storeOutstanding(req)�������㲥����ֹ�Լ����ڴ����view����Ȼ������Լ������ڵ�Ļ���ִ��leaderProcReq�����Ĳ�����Ҫ��
���������ﵽop.batchSize��ʱ��ŷ���events.Event�����򷵻ؿա������ز�Ϊ��ʱ��processMessage�᷵��һ���ǿ��¼���Ȼ�󴫵ݵ�ProcessEvent
����default��֧������pbft-core��ProcessEventģ�鴦��(RequestBatch�¼�)

## pbftЭ�����

### ���ڵ��յ�RequestBatch����

1. ����<hash(req), req>��reqBatchStore��outstandingReqBatches,���־û�( instance.consumer.StoreState(k,v) )
2. ��һ����hash(req)��صļ�ʱ��
3. �жϵ�ǰ�ڵ��ǲ������ڵ㣬�����sendPrePrepare


#### ���ڵ㷢��PrePrepare����
1. �ȵõ����к�n(instance.seqNo + 1)
2. ��������Ѿ��յ�����ժҪ��ͬview��ͬ�����к�n��ͬ�ģ��򷵻�
3. ��n����watermarks�䣬��n > h + L/2 ����
4. ��n����viewChangeSeqNo,��Ϊ��Ҫview-change���ڵ㣬����

``` go
func (instance *pbftCore) updateViewChangeSeqNo() {
	if instance.viewChangePeriod <= 0 {
		return
	}
	// Ensure the view change always occurs at a checkpoint boundary
	instance.viewChangeSeqNo = instance.seqNo + instance.viewChangePeriod*instance.K - instance.seqNo%instance.K
	logger.Debugf("Replica %d updating view change sequence number to %d", instance.id, instance.viewChangeSeqNo)
}
```
���viewchangeperiod����Ϊ0�򲻻�ı�viewChangeSeqNo

5. ���������������㡣����pre-prepare��Ϣ
``` go
	preprep := &PrePrepare{
		View:           instance.view,     // ��ǰview
		SequenceNumber: n,                 // ��Ϣ��
		BatchDigest:    digest,
		RequestBatch:   reqBatch,
		ReplicaId:      instance.id,       //���ڵ�id
	}
```
�� prePrepare, digest����cert����־û�qset(?)
6. �㲥pre-Prepare��Ϣ
7. maybeSendCommit  ��Ŀǰ�����ر����ף�


### recvPrePrepare��������

1. �������view-change,�������Pre-Prepare��Ϣ
2. ����յ���Pre-Prepare����id���ǵ�ǰview�����ڵ㣬�������Pre-Prepare��Ϣ��viewһ�������ڵ�һ�� pbftCore.primary������
3. ���յ���view��pbft-core��view��һ�£���n����watermarks��Ļ������������Ϣ
4. ��n����viewChangeSeqNo,����viewChange��Ϣ������
5. ���յ���ͬ���кŵ���Ϣʱ�������Ϣ�岻ͬ������view-change
���򣬽��յ���prePrepare, digest����cert��

6. ��reqBatchStore�����ڵ�ǰPrePrepare��Ϣ��ժҪʱ�����ȼ���ժҪ�����ժҪ���յ���ժҪһ�£���ժҪ��¼
��reqBatchStore��outstandingReqBatches�У����־û���reqBatch

7.��ǰ�ڵ㲻�����ڵ㲢�����Pre-Prepare��Ϣ֮ǰû�з���Prepare��Ϣ�Ļ�������prepare��Ϣ��
``` go
prep := &Prepare{
	View:           preprep.View,
	SequenceNumber: preprep.SequenceNumber,
	BatchDigest:    preprep.BatchDigest,
	ReplicaId:      instance.id,
}
```
�Լ�����recvPrepare���൱���Լ��յ���Prepare��Ϣ��
Ȼ��־û�qset(?)
����instance.innerBroadcast(&Message{Payload: &Message_Prepare{Prepare: prep}})�㲥��Ϣ


### �ڵ��յ�prepare��Ϣ
1. ����յ��������ڵ����Ϣ��������prepare�����������ڵ㷢�ͣ�
2. ���յ���view��pbft-core��view��һ�£���n����watermarks��Ļ������������Ϣ
3. ��ȡcert,����յ�ͬһ�ڵ�ͬһview��ͬһ�����Ϣ�����˳�
4. ��prepare����cert,���־û�pset
5. maybeSendCommit(Ŀǰ�����ر�����)


### �ڵ��յ�commit��Ϣ recvCommit
1. ���յ���view��pbft-core��view��һ�£���n����watermarks��Ļ������������Ϣ
2. ��ȡcert,����յ�ͬһ�ڵ�ͬһview��ͬһ��Ŵ��ڸ�commit��Ϣ�����������Ϣ
3. ���commit��cert��
4. ����msg�Ƿ�����commited�����������㣬����ǰ�����outstandingReqBatchesɾ��
ִ��δ��ɵ�batch,ִ�����������кŵ���viewChangeSeqNo������view-change

#### ִ��δ��ɵ�batch executeOutstanding()
���˼·��ÿ��һ��commit��ִ������ûִ����ģ���������һ��ִ�гɹ��򷵻أ��������ִ��
1. ���instance.currentExec��ǰ����ִ�У��˳�
2. ִ������ûִ�����,ִ�гɹ�һ�ξͷ���
``` go
for idx := range instance.certStore {
	if instance.executeOne(idx) {
		break
	}
}
```

#### ִ��ĳһ��commit executeOne(n)
1. ���n������lastExec+1������false(Ϊ�˱�֤����ִ��)
�����lastExec��ʼ����getLastSeqNo���
2. ���������skipInProgress���򷵻�false
skipInProgress �� �ڷ�����һ���������������ѡ��һ���µ���������
3. �����req������commited�������򷵻�false
4. ����ǿ�����instance.execDoneSync()
����instance.consumer.execute(idx.n, reqBatch)����ִ��״̬

### obcbatch execute
1. �Ѽ���ִ�еĽ��׷���txs
2. �������ִ�н��׵Ľڵ��ʱ���
3. ����op.stack.Execute(meta, txs)   ����ִ̨�У�ִ������յ�executedEvent��



## �㲥��ϢС��

| ��Ϣ        | ����   |
| :--------:   | :-----:  |
| Message_PrePrepare     | sendPrePrepare  |
| Message_Prepare        |   recvPrePrepare |
| Message_Commit        |    maybeSendCommit |
| Message_Checkpoint     | Checkpoint  |
| Message_FetchRequestBatch        |   fetchRequestBatches |
| Message_ViewChange        |    sendViewChange |
| Message_NewView        |   sendNewView |
| Message_Prepare        |    processNewView2 |
ADT LinkList{
	数据对象：
	数据关系：
	基本操作:
		CreateNode(ManType man, LNode* next);
			操作结果：生成一个新节点并用man和next初始化它，
			返回新节点的地址
		InsertNode(LNode* nowNode,LNode* newNode);
			初始条件： nowNode及newNode非空
			操作结果：将newNode 插到 nowNode之后，返回操作结果
		RemoveNode(LNode * pre);
			初始条件： pre及pre->next非空
			操作结果：删除pre节点后面的节点



}ADT LinkList



int main(){
	输入初始密码m 和人数n
	创建链表并存入密码和编号
	for(i =0;i<n;i++){
		
		输入第i个人的密码password
		创建新节点并用I 和 password初始化
		if(i == 0){
			将新节点的下一个节点设为他自身
			头节点指针指向新节点
			
		}else{
			将新节点插入链表尾部
		}
		链表尾部指针指向新节点
	}
	
	while(链表非空){
		找到报m的那个人
		输出其编号
		将该节点的密码设为新的m值
		删除该节点	
	}
	结束程序
}

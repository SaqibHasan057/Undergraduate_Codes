#include "linkedList.cpp"
#define TABLE_SIZE 100
#define HUGE 100000

int hashFunction(char *ipAdress){
	int sum = 0;
	for(int i=0;i<strlen(ipAdress);i++){
		sum+=ipAdress[i];
	}
	sum=(sum*sum*7)*29+13;
	sum=sum%TABLE_SIZE;
	return sum;
}



class routingHashTable{
	linkedList *list;
	int numberOfElements;
	char ipAdressOfTable[100];

public:

	routingHashTable(){
		list = new linkedList[TABLE_SIZE];
		numberOfElements=0;
		strcpy(ipAdressOfTable,"");
	}

	routingHashTable(char *ipAdress){
		list = new linkedList[TABLE_SIZE];
		numberOfElements=0;
		strcpy(ipAdressOfTable,ipAdress);
	}

	void insertIntoTable(char *ipAdress,char *nextHop,int cost){
		int index  = hashFunction(ipAdress);
		list[index].insertElement(ipAdress,nextHop,cost);
	}

	void change(char *ipAdress,char *nextHop,int newCost){
		int index = hashFunction(ipAdress);
		linkedListNode *node = list[index].getNode(ipAdress);
		node->setNextHop(nextHop);
		node->setCost(newCost);
	}

	

	

	linkedListNode *getNodeFromTable(char *ipAdress){
		int index = hashFunction(ipAdress);
		linkedListNode *node = list[index].getNode(ipAdress);
		return node;
	}

	bool contain(char *ipAdress){
		int index = hashFunction(ipAdress);
		return list[index].contains(ipAdress);
	}

	void printRoutingTable(){
		cout<<"destination           nextHop           cost"<<endl;
		for(int i=0;i<TABLE_SIZE;i++){
			if(!list[i].emptyList())list[i].printLinkedList();
		}
	}

	void changeValueAsHop(char *ipAdressAsHop,int newCost){
		for(int i=0;i<TABLE_SIZE;i++)if(!list[i].emptyList())list[i].changeValueAsHop(ipAdressAsHop,newCost);
	}
    
    void updateValueAsHop(char *ipAdressAsHop,int updateCost){
		for(int i=0;i<TABLE_SIZE;i++)if(!list[i].emptyList())list[i].updateValueAsHop(ipAdressAsHop,updateCost);
	}

    void setCorrectingValuesAfterLinkDown(linkedList edgeList,char *ipAdressDown){
    	for(int i=0;i<TABLE_SIZE;i++){
    		if(!list[i].emptyList())list[i].correctInfinityValues(edgeList,ipAdressDown);
    	}
    }

	string serialize(){
		string final="";
		string address(ipAdressOfTable);
		final+=address+"\n";
		for(int i=0;i<TABLE_SIZE;i++){
			if(!list[i].emptyList())final+=list[i].getStringFormat();
		}
		return final;
	}

	linkedList* getListArray(){
		return this->list;
	}

	char *getIpAdressOfTable(){
		return ipAdressOfTable;
	}

	void setIpAdressOfTable(string ipAdressOfTable){
		const char* x= ipAdressOfTable.c_str();
		strcpy(this->ipAdressOfTable,x);
	}

	void setIpAdressOfTable(char *ipAdressOfTable){
		strcpy(this->ipAdressOfTable,ipAdressOfTable);
	}
};


void updateLinkedList(linkedList tableList,char *ipAdressX,char *ipAdressY,routingHashTable tableFromTheOtherSide,int distance_X_TO_Y,char *hop_X_TO_Y){
	linkedListNode *temp = tableList.getHead();
	//cout<<temp->getIpAdress()<<endl;
	while(temp!=0){
		int distance_X_TO_Z = temp->getCost();
		int distance_Y_TO_Z ;
		char splitHorizontalTest[100];
		if(!strcmp(temp->getIpAdress(),ipAdressY)){
			distance_Y_TO_Z = 0;
			strcpy(splitHorizontalTest,ipAdressY);
		}
		else {
			distance_Y_TO_Z = tableFromTheOtherSide.getNodeFromTable(temp->getIpAdress())->getCost();
			strcpy(splitHorizontalTest,tableFromTheOtherSide.getNodeFromTable(temp->getIpAdress())->getNextHop());	
		}	
		
		if( (distance_X_TO_Y+distance_Y_TO_Z<=distance_X_TO_Z) || ( !strcmp(temp->getNextHop(),ipAdressY) && strcmp(splitHorizontalTest,ipAdressX) ) ){
			temp->setCost(distance_X_TO_Y+distance_Y_TO_Z);
	    	temp->setNextHop(ipAdressY);
	    	//cout<<ipAdressY<<"updates "<<temp->getIpAdress()<<"to "<<temp->getCost()<<" "<<temp->getNextHop()<<endl;
	    }
		temp=temp->getNext();
	}
}

void updateHashTable(routingHashTable toBeUpdated,routingHashTable tableFromTheOtherSide,char *ipAdressY,int edgeCost){
	linkedList *listOfTheHashTable = toBeUpdated.getListArray();
	//cout<<"OKAY"<<endl;
	int distance_X_TO_Y = edgeCost;
	char hop_X_TO_Y[100];
	strcpy(hop_X_TO_Y,toBeUpdated.getNodeFromTable(ipAdressY)->getNextHop());
	char ipAdressX[100];
	strcpy(ipAdressX,toBeUpdated.getIpAdressOfTable());

	for(int i=0;i<TABLE_SIZE;i++){
		//cout<<"HEY "<<distance_X_TO_Y<<endl;
		//cout<<i<<endl;
		if(!listOfTheHashTable[i].emptyList()){
			updateLinkedList(listOfTheHashTable[i],ipAdressX,ipAdressY,tableFromTheOtherSide,distance_X_TO_Y,hop_X_TO_Y);
		}
	}
}

routingHashTable deserializeTable(string stream){
	routingHashTable table;
	istringstream iss(stream);
	string line;
	getline(iss,line);
	table.setIpAdressOfTable(line);
	while(getline(iss,line)){
		istringstream parse(line);
		char a[100],b[100];
		int c;
		parse>>a>>b>>c;
		table.insertIntoTable(a,b,c);
	}
	return table;
}



string packetCreation(char *ipAdress,char *message,int messageLength){
	string ret ="frwd ";
	string number1(ipAdress);
	string number2(message);
	stringstream ss;
	ss<<messageLength;
	string number3 = ss.str();
	ret+=number1+" "+number3+" "+number2;
	return ret;
}

void packetExtraction(char *packet,char *ipAdress,char *message,int *messageLength){
	string pack(packet);
	stringstream word(pack);
	string number1;
	string number2;
	int number3;
	word>>number1;
	word>>number1;
	word>>number3;
	getline(word,number2);
	number2=number2.substr(1,number2.length()-1);
	strcpy(ipAdress,number1.c_str());
	strcpy(message,number2.c_str());
	*messageLength=number3;
}



/*int main(){
	routingHashTable table;
	table.insertIntoTable("192.168.10.1","192.168.10.4",20);
	table.insertIntoTable("192.168.10.2","192.168.10.5",23);
	table.insertIntoTable("192.168.10.3","192.168.10.6",90);
	table.printRoutingTable();
	return 0;
}*/

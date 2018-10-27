#include "hashTable.cpp"




routingHashTable router;
routingHashTable routern;
routingHashTable routerm;
linkedList neighbours;
linkedList neighboursInitialEdgeCost;

void readRouterTable(routingHashTable routingTable,char *ipAdress,char *file){

	ifstream topoFile;
	topoFile.open(file);
	char router1[100];
	char router2[100];
	int costOfPath;

	while(topoFile.good()){

		topoFile>>router1>>router2>>costOfPath;
		if( !strcmp(router1,ipAdress ) ){

			if(routingTable.contain(router2))routingTable.change(router2,router2,costOfPath);
			else routingTable.insertIntoTable(router2,router2,costOfPath);
			neighbours.insertElement(router2,"1",0);
			neighboursInitialEdgeCost.insertElement(router2,router2,costOfPath);

		}
		else if( !strcmp(router2,ipAdress) ){

			if(routingTable.contain(router1))routingTable.change(router1,router1,costOfPath);
			else routingTable.insertIntoTable(router1,router1,costOfPath);
			neighbours.insertElement(router1,"1",0);
			neighboursInitialEdgeCost.insertElement(router1,router1,costOfPath);

		}
		else{

			if(!routingTable.contain(router1))routingTable.insertIntoTable(router1,"    -    ",INFINITY);
			if(!routingTable.contain(router2))routingTable.insertIntoTable(router2,"    -    ",INFINITY);

		}


		//cout<<router1<<" "<<router2<<" "<<costOfPath<<endl;
	}
	//cout<<"OVER"<<endl;
}

void cleanCharBuffer(char *buffer,int length){
	for(int i=0;i<length-1;i++){
		buffer[i]='\0';
	}
}

void linkDownCheck(){
	linkedListNode *temp = neighbours.getHead();
	while(temp!=0){
		if(temp->getCost()>=3 && temp->getNextHop()[0]=='1'){
			router.changeValueAsHop(temp->getIpAdress(),INFINITY);
			temp->setCost(-1);
			temp->setNextHop("0");
			//cout<<"hello"<<endl;
			//router.printRoutingTable();
		}
		//else if(temp->getNextHop()[0]=='1') cout<<temp->getIpAdress()<<" is still up with cost "<<temp->getCost()<<endl;
		temp=temp->getNext();
	}
}

void changeCost(char *ipAdress,int newCost,linkedList listOfEdges){

	listOfEdges.getNode(ipAdress);

	int oldCost = neighboursInitialEdgeCost.getNode(ipAdress)->getCost();

	router.updateValueAsHop(ipAdress,newCost-oldCost);

	neighboursInitialEdgeCost.getNode(ipAdress)->setCost(newCost);
}




int main(int argc,char *argv[]){
	
	router.setIpAdressOfTable(argv[1]);
	readRouterTable(router,argv[1],argv[2]);
	router.printRoutingTable();
	//neighbours.printLinkedList();
	//neighboursInitialEdgeCost.printLinkedList();
	//cout<<router.getIpAdressOfTable()<<endl;
	

	int sockfd; 
	int bind_flag;
	int bytes_received;
	socklen_t addrlen;
	char buffer[1024];
	struct sockaddr_in server_address;
	struct sockaddr_in client_address;
	struct sockaddr_in out;




	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(4747);
	inet_pton(AF_INET,argv[1], &server_address.sin_addr);
	
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	
	bind_flag = bind(sockfd, (struct sockaddr*) &server_address, sizeof(sockaddr_in));
	
	if(bind_flag==0)printf("successful bind\n");

	out.sin_family = AF_INET;
	out.sin_port = htons(4747);
	//server_address.sin_addr.s_addr = inet_addr("192.168.10.100");
	inet_pton(AF_INET,"192.168.10.2",&out.sin_addr);
	

	while(true){
		cleanCharBuffer(buffer,1024);
		linkDownCheck();
		bytes_received = recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr*) &client_address, &addrlen);

		/*
		printf("[%s : %hu]:\n %s\n", inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port), buffer);
		printf("%hu\n",client_address.sin_port);
		printf("%u\n",client_address.sin_addr.s_addr);
		*/
		
		
		


		
	if(buffer[0]=='s' && buffer[1]=='h'){
		router.printRoutingTable();
	}
	else if(buffer[0]=='s' && buffer[1]=='e'){
		char ipAdress1[100];
		char ipAdress2[100];
		char messageLength[100];
		int messageLengthInt;

		inet_ntop(AF_INET,buffer+4,ipAdress1,sizeof(ipAdress1));
		inet_ntop(AF_INET,buffer+8,ipAdress2,sizeof(ipAdress2));
		inet_ntop(AF_INET,buffer+12,messageLength,sizeof(messageLength));

		
		if(messageLength[1]=='.')messageLengthInt = (messageLength[0]-'0');
		else messageLengthInt= (messageLength[0]-'0')*10 + (messageLength[1]-'0');
		char message[messageLengthInt+10];

		strcpy(message,buffer+14);

		//cout<<ipAdress1<<" "<<ipAdress2<<" "<<messageLengthInt<<" "<<message<<endl;

		cleanCharBuffer(buffer,1024);

		string get =packetCreation(ipAdress2,message,messageLengthInt);
		strcpy(buffer,get.c_str());

		//cout<<buffer<<endl;

		if(router.getNodeFromTable(ipAdress2)->getCost()<INFINITY){
			inet_pton(AF_INET,router.getNodeFromTable(ipAdress2)->getNextHop(),&out.sin_addr);
			int sent_bytes=sendto(sockfd, buffer, 1024, 0, (struct sockaddr*) &out, sizeof(sockaddr_in));

			cout<<message<<" "<<messageLengthInt<<" forwarded to "<<router.getNodeFromTable(ipAdress2)->getNextHop()<<endl;
		}
	    else cout<<"Packet dropped"<<endl;
		
	}
	else if(buffer[0]=='f' && buffer[1]=='r'){
		char ipAdressDest[100];
		char message[200];
		int messageLength;

		packetExtraction(buffer,ipAdressDest,message,&messageLength);

		//cout<<buffer<<ipAdressDest<<endl;

		if(!strcmp(router.getIpAdressOfTable(),ipAdressDest)){
			cout<<message<<" packet reached destination"<<endl;
		}
		else{

			if(router.getNodeFromTable(ipAdressDest)->getCost()<INFINITY){
				inet_pton(AF_INET,router.getNodeFromTable(ipAdressDest)->getNextHop(),&out.sin_addr);
				int sent_bytes=sendto(sockfd, buffer, 1024, 0, (struct sockaddr*) &out, sizeof(sockaddr_in));
				
				cout<<message<<" "<<messageLength<<" forwarded to "<<router.getNodeFromTable(ipAdressDest)->getNextHop()<<endl;
			}
			else cout<<"Packet dropped"<<endl;

		}
	}
	else if(buffer[0]=='c' && buffer[1]=='l'){

		cleanCharBuffer(buffer,1024);

		string send = router.serialize();
		strcpy(buffer,send.c_str());

		linkedListNode *neighbourIterator = neighbours.getHead();

		while(neighbourIterator!=0){

			neighbourIterator->setCost(neighbourIterator->getCost()+1);
			char address[100];
			strcpy(address,neighbourIterator->getIpAdress());
			inet_pton(AF_INET,address,&out.sin_addr);
		    int sent_bytes=sendto(sockfd, buffer, 1024, 0, (struct sockaddr*) &out, sizeof(sockaddr_in));
		    neighbourIterator=neighbourIterator->getNext();
		}
		
	}
	else if(buffer[0]=='c' && buffer[1]=='o'){
		char ipAdress1[100];
		char ipAdress2[100];
		char newCost[100];
		inet_ntop(AF_INET,buffer+4,ipAdress1,sizeof(ipAdress1));
		inet_ntop(AF_INET,buffer+8,ipAdress2,sizeof(ipAdress2));
		inet_ntop(AF_INET,buffer+12,newCost,sizeof(newCost));
		int costInInt;
		if(newCost[1]=='.')costInInt = (newCost[0]-'0');
		else costInInt= (newCost[0]-'0')*10 + (newCost[1]-'0');

		//cout<<ipAdress1<<" "<<ipAdress2<<" "<<costInInt<<endl;
		//cout<<router.getIpAdressOfTable()<<endl;
		
		if( !strcmp(ipAdress1,router.getIpAdressOfTable()) )changeCost(ipAdress2,costInInt,neighboursInitialEdgeCost);
		else changeCost(ipAdress1,costInInt,neighboursInitialEdgeCost);

	}
	else if (buffer[0]=='1'){

		string tableString(buffer);
		routingHashTable newTable = deserializeTable(tableString);
		neighbours.getNode(newTable.getIpAdressOfTable())->setCost(0);
		neighbours.getNode(newTable.getIpAdressOfTable())->setNextHop("1");
		int edgeCost = neighboursInitialEdgeCost.getNode(newTable.getIpAdressOfTable())->getCost();
		//cout<<newTable.getIpAdressOfTable()<<"has arrived!!!"<<edgeCost<<endl;
		updateHashTable(router,newTable,newTable.getIpAdressOfTable(),edgeCost);
	}		

	}
	
	return 0;
}




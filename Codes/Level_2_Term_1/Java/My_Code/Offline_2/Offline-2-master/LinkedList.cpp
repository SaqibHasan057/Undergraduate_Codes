#include<iostream>
using namespace std;

class Element {
private:
    Element * next;
	Element * prev;
	int value;
public:
	void setNext(Element *n) {
		next = n;
	}
	Element * getNext() {
		return next;
	}
	void setPrev(Element *p) {
		prev  = p;
	}
	Element * getPrev() {
		return prev;
	}
	void setValue(int v) {
		value = v;
	}
	int getValue() {
		return value;
	}
};

class LinkedListBase {
protected:
	Element * head;
	Element * tail;
	int size;
public:
	LinkedListBase() {
        head=new Element;
        tail=new Element;
		head->setNext(tail);
		tail->setPrev(head);
		size = 0;
    }
	int getSize() {
		return size;
	}
	~LinkedListBase() {
		delete head;
		delete tail;
	}
};

class LinkedList: public LinkedListBase {
    public:
    void add(Element e);
    void add(int index, Element e);
    void addFirst(Element e);
    void addLast(Element e);
    void clear();
    bool contains(Element e);
    Element get(int index);
    Element getFirst();
    Element getLast();
    int indexOf(Element e);
    int lastIndexOf(Element e);
    Element remove(int index);
    bool remove(Element e);
    Element removeFirst();
    bool removeFirstOccurrence(Element e);
    Element removeLast();
    bool removeLastOccurrence(Element e);
    int size();
    bool isEmpty();
    string toString();
};

void LinkedList::add(Element e)
{
    Element *newNode;
    newNode=new Element;
    newNode->setValue(e.getValue());
    if(head->getNext()==tail)
    {
        head->setNext(newNode);
        newNode->setNext(tail);
        newNode->setPrev(head);
        tail->setPrev(newNode);
    }
    else
    {
        tail->getPrev()->setNext(newNode);
        newNode->setPrev(tail->getPrev());
        newNode->setNext(tail);
        tail->setPrev(newNode);
    }
    LinkedListBase::size++;
}

void LinkedList::add(int index,Element e)
{
    if(index<=LinkedListBase::size)
    {
        Element *temp;
        temp=head;
        Element *newNode;
        newNode=new Element;
        newNode->setValue(e.getValue());
        for(int i=0;i<=index;i++)temp=temp->getNext();
        temp->getPrev()->setNext(newNode);
        newNode->setPrev(temp->getPrev());
        newNode->setNext(temp);
        temp->setPrev(newNode);
        LinkedListBase::size++;
    }
}

void LinkedList::addFirst(Element e)
{
    Element *newNode;
    newNode=new Element;
    newNode->setValue(e.getValue());
    if(head->getNext()==tail)
    {
        head->setNext(newNode);
        newNode->setNext(tail);
        newNode->setPrev(head);
        tail->setPrev(newNode);
    }
    else
    {
       head->getNext()->setPrev(newNode);
       newNode->setNext(head->getNext());
       head->setNext(newNode);
       newNode->setPrev(head);
    }
    LinkedListBase::size++;

}

void LinkedList::addLast(Element e)
{
    Element *newNode;
    newNode=new Element;
    newNode->setValue(e.getValue());
    if(head->getNext()==tail)
    {
        head->setNext(newNode);
        newNode->setNext(tail);
        newNode->setPrev(head);
        tail->setPrev(newNode);
    }
    else
    {
        tail->getPrev()->setNext(newNode);
        newNode->setPrev(tail->getPrev());
        newNode->setNext(tail);
        tail->setPrev(newNode);
    }
    LinkedListBase::size++;
}

void LinkedList::clear()
{
    if(head->getNext()!=tail)
    {
        Element *prev,*temp;
        temp=head->getNext();
        while(temp!=tail)
        {
            prev=temp;
            temp=temp->getNext();
            delete prev;
        }
        LinkedListBase::size=0;
        head->setNext(tail);
		tail->setPrev(head);
    }
}


bool LinkedList::contains(Element e)
{
    if(head->getNext()!=tail)
    {
        Element *temp;
        temp=head->getNext();
        while(temp!=tail)
        {
            if(temp->getValue()==e.getValue())return true;
            temp=temp->getNext();
        }
    }
    return false;
}

Element LinkedList::get(int index)
{
    if(head->getNext()!=tail)
    {
        Element *temp;
        temp=head->getNext();
        for(int i=0;i<index;i++)
        {
            temp=temp->getNext();
        }
        return *temp;
    }
}

Element LinkedList::getFirst()
{
    if(head->getNext()!=tail)
    {
        Element newNode,*temp;
        temp=head->getNext();
        newNode.setValue(temp->getValue());
        return newNode;
    }
}

Element LinkedList::getLast()
{
    if(head->getNext()!=tail)
    {
        Element newNode,*temp;
        temp=tail->getPrev();
        newNode.setValue(temp->getValue());
        return newNode;
    }
}

int LinkedList::indexOf(Element e)
{
    Element *temp;
    temp=head->getNext();
    int index=0;
    while(temp!=tail)
    {
        if(temp->getValue()==e.getValue())return index;
        temp=temp->getNext();
        index++;
    }
    return -1;
}

int LinkedList::lastIndexOf(Element e)
{
    Element *temp;
    temp=head->getNext();
    int index=0;
    int indexNeeded=-1;
    while(temp!=tail)
    {
        if(temp->getValue()==e.getValue())indexNeeded=index;
        temp=temp->getNext();
        index++;
    }
    return indexNeeded;
}

Element LinkedList::remove(int index)
{
    if(head->getNext()!=tail){
            Element *temp;
            temp=head->getNext();
            for(int i=0;i<index;i++)
            {
                 temp=temp->getNext();
            }
            temp->getPrev()->setNext(temp->getNext());
            temp->getNext()->setPrev(temp->getPrev());
            LinkedListBase::size--;
            return *temp;
    }
}

bool LinkedList::remove(Element e)
{
    if(head->getNext()==tail)return false;
    Element *temp;
    temp=head->getNext();
    while(temp!=tail)
    {
        if(temp->getValue()==e.getValue())
        {
            temp->getPrev()->setNext(temp->getNext());
            temp->getNext()->setPrev(temp->getPrev());
            LinkedListBase::size--;
            return true;
        }
        temp=temp->getNext();
    }
    return false;
}

Element LinkedList::removeFirst()
{
    if(head->getNext()!=tail)
    {
        Element *temp;
        temp=head->getNext();
        head->setNext(temp->getNext());
        temp->getNext()->setPrev(head);
        LinkedListBase::size--;
        return *temp;
    }

}

bool LinkedList::removeFirstOccurrence(Element e)
{
    if(head->getNext()==tail)return false;
    int index=indexOf(e);
    if(index!=-1)
    {
        remove(index);
        return true;
    }

}

Element LinkedList::removeLast()
{
    if(head->getNext()!=tail)
    {
        Element *temp;
        temp=tail->getPrev();
        temp->getPrev()->setNext(tail);
        tail->setPrev(temp->getPrev());
        LinkedListBase::size--;
        return *temp;
    }

}

bool LinkedList::removeLastOccurrence(Element e)
{
    if(head->getNext()==tail)return false;
    int index=lastIndexOf(e);
    if(index!=-1)
    {
        remove(index);
        return true;
    }
}

int LinkedList::size()
{
    return LinkedListBase::size;
}

bool LinkedList::isEmpty()
{
    if(LinkedListBase::size==0)return true;
    else return false;
}

string LinkedList::toString()
{
    string ret="";
    Element *temp;
    temp=head->getNext();
    while(temp!=tail)
    {
        int val,index=0;
        char adder[10000];
        val=temp->getValue();
        while(val!=0)
        {
            adder[index]=val%10+48;
            index++;
            val=val/10;
        }
        index--;
        while(index>=0)
        {
            ret+=adder[index];
            index--;
        }
        if(temp->getNext()!=tail)ret+=",";
        temp=temp->getNext();
    }
    return ret;
}


// main for checking the functions of LinkedList
int main() {
	LinkedList ll;
	cout << ll.getSize() << endl;
	Element e1,e2,e3,e4,e5,e6,e7,e8,e9,e10;
	e1.setValue(11);
	e2.setValue(22);
	e3.setValue(33);
	e4.setValue(44);
	e5.setValue(55);
	e6.setValue(11);
	e7.setValue(77);
	e8.setValue(88);
	e9.setValue(99);
	e10.setValue(55);
	ll.add(e1);
	ll.add(e2);
	ll.add(e3);
	ll.add(e4);
	ll.add(e5);
	ll.add(e6);
	cout <<ll.size()<< endl;
	cout<<ll.toString()<<endl;
	ll.addFirst(e6);
	ll.addLast(e7);
	cout <<ll.size()<< endl;
	cout<<ll.toString()<<endl;
	ll.clear();
	cout <<ll.size()<< endl;
	if(ll.isEmpty())cout<<"List is empty!"<<endl;
	cout<<ll.toString()<<endl;
	ll.addFirst(e1);
	ll.addFirst(e7);
	cout <<ll.size()<< endl;
	cout<<ll.toString()<<endl;
	ll.clear();
	ll.add(e1);
	ll.add(e2);
	ll.add(e3);
	ll.add(e4);
	ll.add(e5);
	ll.add(e6);
	ll.add(e7);
	ll.add(e8);
	ll.add(e1);
	cout <<ll.size()<< endl;
	cout<<ll.toString()<<endl;
	ll.removeFirstOccurrence(e1);
	cout <<ll.size()<< endl;
	cout<<ll.toString()<<endl;
	ll.removeLastOccurrence(e1);
	cout <<ll.size()<< endl;
	cout<<ll.toString()<<endl;
	ll.removeFirst();
	ll.removeLast();
	cout <<ll.size()<< endl;
	cout<<ll.toString()<<endl;
	ll.add(2,e9);
	cout <<ll.size()<< endl;
	cout<<ll.toString()<<endl;
	if(ll.contains(e9))cout<<"YES"<<endl;
	cout <<ll.getFirst().getValue()<< endl;
	cout <<ll.getLast().getValue()<< endl;
	ll.remove(e8);
	ll.removeFirstOccurrence(e8);
	ll.removeLastOccurrence(e8);
	cout <<ll.size()<< endl;
	cout<<ll.toString()<<endl;
	return 0;
}


public class LinkedStack{
    private static class Node {
        int data;
        Node next;

        Node(int data){
            this.data = data;
        }
    }

    private Node top ;

    public LinkedStack(){
        top = null;
    }

    public void push(int item){
        Node newNode = new Node(item);
        newNode.next = top;
        top = newNode;
    }
    public int pop(){
        if(isEmpty()){
            throw new RuntimeException("Stack is empty");
        }
        int item = top.data;
        top = top.next;
        return item;
    }

    public int peek(){
        if(isEmpty()){
            throw new RuntimeException("Stack is empty");
        }
        return top.data;
    }

    public boolean isEmpty(){
        return top == null ;
    }

    public int size() {
        int count = 0;
        Node current = top;
        while (current != null){
            count ++;
            current = current.next;
        }
        return count ;
    }
}
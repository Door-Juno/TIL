class Node {
    int data;
    Node link;

    Node(int data) {
        this.data = data;
        this.link = null;
    }
}

class Queue {
    private Node front, rear;

    public Queue() {
        front = rear = null;
    }

    public void enqueue(int item) {
        Node node = new Node(item);
        if (rear != null) rear.link = node;
        else front = node;
        rear = node;
    }

    public int dequeue() {
        if (front == null) throw new RuntimeException("Empty Queue");
        int data = front.data;
        front = front.link;
        if (front == null) rear = null;
        return data;
    }
}
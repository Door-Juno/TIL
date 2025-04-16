from .Example.CircularQueue import CircularQueue

# CircularQueue 상속
class CircularDeque(CircularQueue) :
    def __init__(self, capacity=10):
        # 생성자 호출
        super().__init__(capacity)
    # isEmpty, isFull, size, __str__ 은 상속

    # 이름이 바뀌는 연산들
    def addRear(self, e) : self.enqueue(e) 
    def deleteFront(self) : return self.dequeue()
    def getFront(self) : return self.peek()

    # 새로 구현되는 연산들
    def addFront(self, e) :
        if not self.isFull() :
            self.array[self.front] = e
            self.front = (self.front -1 + self.capacity) % self.capacity
        else : pass

    def deleteRear(self) :
        if not self.isEmpty() :
            e = self.array[self.rear]
            self.rear = (self.rear -1 + self.capacity) % self.capacity
            return e
        else : pass

    def getRear(self):
        if not self.isEmpty() :
            return self.array[self.rear]
        else : pass
# 우선순위 큐 Priority Queue
### 1. 우선순위 큐
우선순위 큐는 일반 큐와 달리 요소마다 **우선순위**를 두고, 
**높은 우선순위를 가진 요소를 먼저 삭제하는 자료구조이다.**

일반 큐 : 먼저 들어온 순서
우선순위 큐 : 우선순위가 높은 순서
> 최적 경로를 찾는 다익스트라 알고리즘 등에 사용된다.

### 2. 우선순위 큐의 ADT

| 연산 이름       | 설명 |
|----------------|------|
| `isEmpty()`    | 우선순위큐가 비어있으면 `True`, 아니면 `False`를 반환한다. |
| `isFull()`     | 우선순위큐가 가득 차 있으면 `True`, 아니면 `False`를 반환한다. |
| `enqueue(e)`   | 우선순위를 가진 요소 `e`를 삽입한다. |
| `dequeue()`    | 가장 우선순위가 높은 요소를 꺼내서 반환한다. |
| `peek()`       | 가장 우선순위가 높은 요소를 삭제하지 않고 반환한다. |

### 3. 우선순위 큐의 시간 복잡도

| 구현 방법 | 시간 복잡도 (삽입/삭제) | 특징 |
|-----------|-------------------------|------|
| 정렬되지 않은 배열/리스트 | O(1) / O(n) | 삽입 빠름, 삭제 느림 |
| 정렬된 배열/리스트       | O(n) / O(1) | 삽입 느림, 삭제 빠름 |
| **이진 힙(Binary Heap)** | **O(log n) / O(log n)** | 가장 효율적, 실무 사용 |

> 대부분의 언어에서 `PriorityQueue`는 내부적으로 **Heap**으로 구현됨

### 4. Python : 우선순위 큐 구현
``` python 
class PriorityQueue :
    def __init__(self, capacity = 10):
        self.capacity = capacity
        self.array = [None] * capacity
        self.size = 0

    def isEmpty(self) : return self.size == 0
    def isFull(self) : return self.size == self.capacity

    def enqueue(self, e):
        if not self.isFull() :
            self.array[self.size] = e
            self.size += 1

    def findMaxIndex(self):
        if self.isEmpty() : return -1
        highest = 0
        for i in range(1,self.size):
            if self.array[i] > self.array[highest]:
                highest = i
        return highest
    
    def dequeue(self):
        highest = self.findMaxIndex()
        if highest != -1 :
            self.size -= 1
            # 튜플 활용해 마지막으로 이동
            self.array[highest],self.array[self.size] = self.array[self.size] , self.array[highest]
            return self.array[self.size]
        
    def peek(self) :
        highest = self.findMaxIndex()
        if highest != -1 :
            return self.array[highest]
        
    def __str__(self):
        return str(self.array[0:self.size])

```

### 5. 마무리하며

| 큐 종류       | 우선순위 | 삽입 위치     | 삭제 대상           |
|---------------|----------|----------------|----------------------|
| 일반 큐       | 없음     | 뒤             | 앞                   |
| 우선순위 큐   | 있음     | 아무 위치 가능 | 우선순위 높은 요소   |

> `PriorityQueue`는 **힙 자료구조의 실용적 활용 예**이며,  
> 많은 알고리즘에서 **핵심 도구**로 쓰인다.
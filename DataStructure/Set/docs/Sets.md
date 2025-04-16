# Set

### 1. Set이란 ?
Set이란 **중복을 허용하지 않는**자료구조이다.
집합처럼 원소의 존재 여부에 초점을 맞춰 관리할 수 있다.
또 순서에 의미를 두지 않기 때문에 보통 순서가 정렬되어있지 않긴 하다만.. 정렬된 set또한 존재한다 !

### 2. Set의 ADT

| 연산 | 설명 |
|------|------|
| `add(x)` | x가 없으면 추가 |
| `remove(x)` | x가 있으면 제거 |
| `contains(x)` | x가 Set에 존재하는지 확인 |
| `size()` | 전체 원소의 개수 반환 |
| `clear()` | 모든 원소 제거 |
| `union`, `intersection`, `difference` | 집합 연산 (언어에 따라 지원 여부 다름) |

### 3. Python : 연결 리스트 기반 Set 구현
``` python
class Node:
    def __init__(self, data, link=None):
        self.data = data
        self.link = link

class LinkedSet:
    def __init__(self):
        self.head = None

    def contains(self, data):
        node = self.head
        while node:
            if node.data == data:
                return True
            node = node.link
        return False

    def add(self, data):
        if not self.contains(data):
            self.head = Node(data, self.head)

    def remove(self, data):
        prev, node = None, self.head
        while node:
            if node.data == data:
                if prev:
                    prev.link = node.link
                else:
                    self.head = node.link
                return
            prev = node
            node = node.link

```

### 4. Set과 List의 차이

| 항목       | Set                     | List        |
|------------|--------------------------|-------------|
| 중복 허용   | ❌                      | ✅          |
| 순서 보장   | ❌ (기본 Set)           | ✅          |
| 탐색 성능   | O(1) (HashSet 기준)     | O(N)        |
| 삽입/삭제   | 평균 O(1)               | O(1) ~ O(N) |


### 마무리 하며
Set은 자주 쓰이지만, 그만큼 단순한 구조 안에 많은 성능 최적화와 자료구조 개념이 담겨 있다.
중복 제거, 빠른 탐색, 집합 연산이 필요할 때 적극 활용해보자.
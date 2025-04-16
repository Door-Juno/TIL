# 버블 정렬(Bubble Sort)
### 1. 버블 정렬이란 ?
두 값을 비교하여 정렬하는 가장 단순한 정렬 알고리즘.
첫 번째 원소부터 시작하여 인접한 두 값을 비교하고 교환하는 과정을 모든 요소를 순회하는 동안 반복한다.
* 반복과정이 1회 끝나면 가장 큰 값이 맨 뒤로 밀려나게 된다.
* 이 과정을 N-1 회 반복한다.


### 2. 버블정렬의 성능
| 케이스         | 시간 복잡도 | 설명                                      |
|----------------|-------------|-------------------------------------------|
| 최선 (Best)    | O(n)        | 이미 정렬된 경우 (`swapped` 최적화 적용 시) |
| 평균 (Average) | O(n²)       | 일반적인 경우 모든 요소를 비교/스왑        |
| 최악 (Worst)   | O(n²)       | 역순 정렬된 배열                           |
| 공간 복잡도    | O(1)        | 추가 메모리 사용 없이 제자리에서 정렬      |
* 거의 모든 다른 정렬 알고리즘보다 느리다. -> 실제로 쓰이진 않음 !
* 그러나 구현이 매우 쉽다는 장점이 있다. (정렬 하면 제일 먼저 배울정도로 쉬움) 

### 3. Python : 버블 정렬 구현
``` python
def BubbleSort(A) :
    n = len(A)
    for i in range(n-1,0,-1):
        bchanged = False
        for j in range(i):
            if(A[j] > A[j+1]):
                A[j], A[j+1] = A[j+1],A[j]
                bchanged = True
        if not bchanged: break
        printStep(A,n-i)

def printStep(A,step):
        print(f"Step {step}: {A}")

# 테스트 메인함수
def test_bubble_sort():
    test_cases = [
        [5, 1, 4, 2, 8],
        [1, 2, 3, 4, 5],
        [10, 9, 8, 7, 6],
        [1],
        [],
        [3, 3, 2, 1, 2]
    ]

    for idx, case in enumerate(test_cases):
        print(f"\n🔍 Test Case {idx + 1}: {case}")
        BubbleSort(case.copy())  # 원본 훼손 방지

test_bubble_sort()
```
```bash
# 출력 결과
🔍 Test Case 1: [5, 1, 4, 2, 8]
Step 1: [1, 4, 2, 5, 8]
Step 2: [1, 2, 4, 5, 8]

🔍 Test Case 2: [1, 2, 3, 4, 5]

🔍 Test Case 3: [10, 9, 8, 7, 6]
Step 1: [9, 8, 7, 6, 10]
Step 2: [8, 7, 6, 9, 10]
Step 3: [7, 6, 8, 9, 10]
Step 4: [6, 7, 8, 9, 10]

🔍 Test Case 4: [1]

🔍 Test Case 5: []

🔍 Test Case 6: [3, 3, 2, 1, 2]
Step 1: [3, 2, 1, 2, 3]
Step 2: [2, 1, 2, 3, 3]
Step 3: [1, 2, 2, 3, 3]
```
* `bChanged`의 역할
    * 변경되었는가? 를 의미한다.
    * 두 요소를 스왑한 경우에 `True`가 된다.
    * 일회전할때 스왑하지 않아 `False`가 된다는 것은 배열이 이미 정렬되어 있다는 의미이므로, `break`를 실행한다.
    * 이미 정렬된 배열에서 불필요한 루프를 방지하는 역할을 한다.

### 4. 버블 정렬의 특징
- 많은 이동 필요 -> 불륨이 클 경우 불리해진다.
- 안정된 정렬 방법
- 대부분 정렬되어 있으면 **매우 효율적**이다.


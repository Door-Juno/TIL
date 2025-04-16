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
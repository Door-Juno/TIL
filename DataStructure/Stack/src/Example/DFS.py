class ArrayStack : 
    def __init__(self, capacity = 100) :
        self.capacity = capacity
        self.array = [None] * capacity
        self.size = 0 

    def isEmpty(self):
        return self.size == 0
    
    def isFull(self):
        return self.size == self.capacity
    
    def push(self, e):
        if not self.isFull() :
            self.array[self.size] = e
            self.size += 1

        else : pass 

    def pop (self):
        if not self.isEmpty():
            e = self.array[self.size-1]
            self.size -= 1
            return e 
        else : pass

    def peek(self) :
        return self.array[self.size-1]
    
    def __str__(self):
        return str(self.array[:self.size][::-1])
    
MAZE_SIZE = 6
map =[[ '1', '1', '1', '1', '1', '1' ],
        [ 'e', '0', '0', '0', '0', '1' ],
        [ '1', '0', '1', '0', '1', '1' ],
        [ '1', '1', '1', '0', '0', 'x' ],
        [ '1', '1', '1', '0', '1', '1' ],
        [ '1', '1', '1', '1', '1', '1' ]]

# 1. 현재 위치 (0,1) push and pop
# 2. pop 한 위치에서 다음 위치로 갈수 있다면 다음 위치 Push
# 3. 다음위치 pop 반복
# 4. Stack 이 다 비워질때 까지
def DFS () :
    print("DFS Start")
    stack = ArrayStack(100)
    stack.push((0,1))

    while not stack.isEmpty() :
        here = stack.pop()
        print(here, end = '->')
        (x,y) = here

        if ( map[y][x] == 'x'):
            print("DFS complete")
            return True

        else :
            map[y][x] = '.'
            if isValidPos(x,y-1) : stack.push((x,y-1))
            if isValidPos(x,y+1) : stack.push((x,y+1))
            if isValidPos(x-1,y) : stack.push((x-1,y))
            if isValidPos(x+1,y) : stack.push((x+1,y))
        print('현재 스택 : ',stack)

    print("DFS ERROR")
    return False


def isValidPos(x,y):
    if 0 <= x < MAZE_SIZE and 0 <= y < MAZE_SIZE :
        if map[y][x] == '0' or map[y][x] == 'x':
            return True
    return False

def main() :
    result = DFS()
    if result : print(' --> 미로탐색 성공')
    else : print(' --> 미로탐색 실패')

if __name__ == "__main__" :
    main()
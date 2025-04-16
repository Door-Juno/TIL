MAZE_SIZE = 6
map =[[ '1', '1', '1', '1', '1', '1' ],
        [ 'e', '0', '0', '0', '0', '1' ],
        [ '1', '0', '1', '0', '1', '1' ],
        [ '1', '1', '1', '0', '0', 'x' ],
        [ '1', '1', '1', '0', '1', '1' ],
        [ '1', '1', '1', '1', '1', '1' ]]

from CircularQueue import CircularQueue

def BFS() :
    q = CircularQueue()
    q.enqueue((0,1))
    print("BFS Start")

    while not q.isEmpty() :
        here = q.dequeue()
        print(here , end = '->')

        x,y = here

        if (map[y][x] == 'x') : 
            return True
        else :
            map[y][x] = '.'
            if isValidPos(x,y-1) : q.enqueue((x,y-1))
            if isValidPos(x,y+1) : q.enqueue((x,y+1))
            if isValidPos(x-1,y) : q.enqueue((x-1,y))
            if isValidPos(x+1,y) : q.enqueue((x+1,y))
    return False

def isValidPos(x,y):
    if 0 <= x < MAZE_SIZE and 0 <= y < MAZE_SIZE :
        if map[y][x] == '0' or map[y][x] == 'x':
            return True
    return False

def main() :
    result = BFS()
    if result : print(' --> 미로탐색 성공')
    else : print(' --> 미로탐색 실패')

if __name__ == "__main__" :
    main()
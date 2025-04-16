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

# 1. 수식을 스캔하다가 피 연산자가 나오면 스택에 push
# 2. 연산자가 나오면, 저장하고 스택에서 pop 두번하고 계산하고, 다시 psuh.
def evalPostfix(expr) :
    s = ArrayStack(100)

    # 수식 스캔
    for token in expr :
        # 연산자를 만나면
        if token in "+-*/" :
            val2 = s.pop()
            val1 = s.pop()

            if (token == '+'): s.push(val1+val2)
            elif (token == '-') : s.push(val1-val2)
            elif(token =='*'): s.push(val1*val2)
            elif(token == '/') : s.push(val1/val2)
        # 피연산자를 만나면
        else :
            s.push(float(token))
    # 모든 순회가 끝마쳤을때, Stack에는 결과값만 남아있음.
    return s.pop()


def Infix_to_Postfix(expr):
    s = ArrayStack(100)
    output = []

    for term in expr :
        if term == '(' :
            s.push('(')
        elif term == ')':
            while not s.isEmpty() :
                op = s.pop()
                if op == '(' :
                    break;
                else :
                    output.append(op)
        elif term in "+-*/":
            while not s.isEmpty() :
                op = s.peek()
                if (precedence(term) <= precedence(op)):
                    output.append(op)
                    s.pop()
                else : break
            s.push(term)
        else :
            output.append(term)
    while not s.isEmpty():
        output.append(s.pop())
    return output

def precedence(op):
    if op == '(' or op == ')' : return 0
    elif op =='+' or op == '-' : return 1
    elif op == '*' or op == '/' : return 2
    else : return -1


def main() :
    # 후위 표기 직접 계산
    postfix_expr = ['8', '2', '/', '3', '-', '3', '2', '*', '+']
    print("후위 표기 계산:", postfix_expr, '-->', evalPostfix(postfix_expr))

    # 중위 → 후위 변환 후 계산
    infix_expr = ['(', '8', '/', '2', ')', '-', '3', '+', '3', '*', '2']
    postfix = Infix_to_Postfix(infix_expr)
    print("중위 표현:", infix_expr)
    print("후위 변환:", postfix)
    print("후위 계산 결과:", evalPostfix(postfix))


if __name__ == "__main__" :
    main()
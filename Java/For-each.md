# 향상된 for문 (for - each)
``` java 
public class main {
    public static void main(String[] args){
        int [] numbers = {1,2,3,4,5};

        for(int i = 0 ; i < numbers.len() ; i ++){
            System.out.println(number[i]);
        }
    }
}
```
기존 for문은 `for(초기식 ; 조건식 ; 증감식)` 을 통해 배열이나 컬렉션의 요소에 접근을 한다.
향상된 for 문에서는 위 식과 달리 요소를 담을 변수와 열거를 할 객체를 나열하여 해당 자료구조의 순회에 대해서는 더 좋은 가독성을 보여준다.
``` java
for(타입 변수명 : 배열 or 컬렉션) {
    //loop
}
```
즉 가장 위에 `numbers` 배열의 순회를 향상된 for문을 이용해 표현해보자.
``` java
public class main () {
    public static void main(String[] args){
        int [] numbers = {1,2,3,4,5};

        for(int x : numbers){
            System.out.println(x);
        }
    }
}
```
for문을 순회하면서 요소를 담을 변수인 `x`는 loop-1 일때 `1`을, loop-2 일때 `2`를 담으며 객체의 시작부터 끝까지 자동적으로 초기화와 저장을 반복한다.

기존 for문 에서는 초기식이 증감에 의해 조건식을 만족하지 못할때 종료를 했지만 향상된 for문에서는 객체의 모든 요소의 개수만큼 반복하면 종료가 된다.

기존 for문에서 처럼 배열의 짝수번째 원소만을 접근 하는등의 index의 조절은 못하지만 단순히 나열이나 순회에 조건에서는 향상된 for문의 가독성이 더 좋다고 할 수 있겠다.

그렇다고 해서 두 for문의 작동 메커니즘에대해서는 달라지는게 없다. 똑같은 메커니즘으로 작동을하며 성능상의 차이는 없다고 본다.

일반적으로는 향상된 for문이 간결한 코드와 좋은 가독성을 지니고 있어 우선적으로 사용하는 걸 권장하므로 
배열과 컬렉션에서는 향상된 for문을 우선적으로 사용하는걸 권장한다.
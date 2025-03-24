# List
순서가 있는 데이터 저장을 지원하는 자료구조이다.
중복을 허용하며 index를 사용하여 데이터에 접근이 가능하다.
### 1. ArrayList vs LinkedList
`ArrayList`는 배열 기반의 동적 리스트이며 데이터 조회 및 순차적 추가에 장점이 있다.
그러나 중간 삽입/삭제가 느리고 배열의 크기 변경시 성능이 저하된다는 단점이 있다.
`LinkedList`는 노드 기반의 동적 리스트이며 중간 삽입/삭제 속도가 빠르지만 데이터 조회 속도가 느리며 메모리 사용량이 크다.

- 데이터의 조회가 중요하다면 -> `ArrayList`를 선택하는 것이 합리적이다.
- 데이터의 삽입과 삭제가 자주 일어난다면 -> `LinkedList`를 선택하는 것이 합리적이다.

### 2. ArrayList 
- ex) 쇼핑몰 장바구니 
``` java
import java.util.ArrayList;

public class ShoppingCart {
    public static void main(String[] args) {
        //ArrayList 객체 생성
        ArrayList<String> cart = new ArrayList<>();

        //상품 추가
        cart.add(item);

        //특정 위치에 요소 추가
        cart.add(index, item);

        //상품 삭제
        cart.remove(item);
        
        //특정 위치의 요소 삭제
        cart.remove(index)

        //특정 위치의 요소 가져오기
        cart.get(intext);

        //특정 위치의 요소 변경
        cart.set(index,changeitem);

        //요소 존재 여부 확인
        cart.contains(item);

        //요소의 위치 찾기
        cart.indexOf(item);

        //리스트가 비어있는지 확인
        cart.isEmpty();

        //리스트 크기 확인
        cart.size();
    }
}
```

### 3. LinkedList
- ex ) 최근 본 상품 기능
``` java 
import java.util.LinkedList;
    public class RecentViewedProducts {
        public static void main(String[] args) {
            LinkedList<String> recent = new LinkedList<>();

            //리스트 끝에 요소 추가
            recent.add(item);

            //특정 위치에 요소 추가
            recent.add(index, item);

            //리스트의 맨 앞에 요소 추가
            recent.addFirst(item);

            //리스트의 맨 뒤에 요소 추가
            recent.addLast(item);

            //첫 번째 요소 제거
            recent.remove();

            //특정 위치 요소 제거
            recent.remove(index);

            //특정 객체 제거
            recent.remove(item);

            //첫번째 요소 제거
            recent.removeFirst();

            //마지막 요소 제거
            recent.removeLast();

            //특정 인덱스의 요소 반환
            recent.get(index);

            //첫번째 요소 반환
            recent.peek();

            //리스트 크기 반환
            recent.size();

    }
}


# 예외처리
### 1. 예외처리란 ?
예외(Exception)는 프로그램 실행 중 예상치 못한 상황(Error)가 발생하는 것을 의미한다.
에러가 발생했을시 프로그램이 종료되지 않고 사용자에게 전달하기 위해 예외처리를 한다.

* 예외가 발생할 수 있는 사유
    * 0으로 나누기 -> `ArithmeticException`
    * 배열 범위를 초과한 접근 -> `ArrayIndexOutOfBoundsException`
    * null 값 참조 -> `NullPointerException`
    * 파일을 찾을 수 없음 -> `FileNotFoundException`
* 예외 처리를 하는 이유
    * 프로그램이 갑자기 종료되지 않도록 하기 위해
    * 예외 발생 시 사용자에게 적절한 메세지를 제공하기 위해
    * 시스템의 안정성을 유지하기 위해

### 2. 예외의 종류
### 2-1. Checked Exception (컴파일러 체크 예와)
* 컴파일 시점에 반드시 예외 처리를 해야 하는 예외
* `try-catch`를 사용하거나 `throws`로 처리해야 함.
* ex) `IOException`,`SQLException`,`FileNotFoundException`

* 예제 : IOException 
``` java
import java.io.File;
import java.io.FileReader;
import java.io.IOException;

public class CheckedExceptionExample {
    public static void main(String[] args) {
        try {
            File file = new File("test.txt");
            FileReader reader = new FileReader(file); // 예외 발생 가능
        } catch (IOException e) {
            System.out.println("파일을 읽는 중 오류 발생: " + e.getMessage());
        }
    }
}
```
`IOException`은 반드시 `Try-catch` 로 예외 처리를 해야한다.

### 2-2. Unchecked Exception (런타임 예외)
* 실행 중(Runtime)에 발생하는 예외
* 컴파일러가 예외 처리를 강제하지 않음
* ex) `NullPointerException`,`ArithmeticException`,`IndexOutOfBoundsException`

* 예제 : NullPointerException
``` java
public class UncheckedExceptionExample {
    public static void main(String[] args) {
        String text = null;
        System.out.println(text.length()); // NullPointerException 발생
    }
}
```
* `NullPointerException`은 런타임에 발생하며, 개발자가 직접 예외 처리를 할 필요는 없다.

### 3. 예외 처리 방법
### 3-1. try - catch - finally 
* `try` 블록 : 예외가 발생할 가능성이 있는 코드를 실행
* `catch` 블록 : 예외를 처리
* `finally` 블록 : 예외 발생 여부와 관계없이 항상 실행된다.

``` java
public class TryCatchExample {
    public static void main(String[] args) {
        try {
            int result = 10 / 0; // 예외 발생
            System.out.println("결과: " + result);
        } catch (ArithmeticException e) {
            System.out.println("예외 발생: 0으로 나눌 수 없습니다!");
        } finally {
            System.out.println("프로그램 종료");
        }
    }
}
```
* `finally`블록은 자원 정리가 필요할 때 유용함 (파일 닫기, DB 연결 해제 등)

### 3-2. throws
* 예외를 직접 처리 하지 않고, 호출한 곳으로 예외를 넘긴다.
* 메서드 선언부에 `trhrow 예외타입`을 명시한다.

``` java
public class ThrowsExample {
    public static void main(String[] args) {
        try {
            divide(10, 0);
        } catch (ArithmeticException e) {
            System.out.println("예외 발생: " + e.getMessage());
        }
    }

    public static void divide(int a, int b) throws ArithmeticException {
        if (b == 0) {
            throw new ArithmeticException("0으로 나눌 수 없습니다.");
        }
        System.out.println("결과: " + (a / b));
    }
}
```

### 3-3. throw
* `throw`를 사용하면 직접 예외를 발생시킬 수 있다.

``` java
public class ThrowExample {
    public static void main(String[] args) {
        try {
            checkAge(15);
        } catch (Exception e) {
            System.out.println("예외 발생: " + e.getMessage());
        }
    }

    public static void checkAge(int age) {
        if (age < 18) {
            throw new IllegalArgumentException("18세 이상만 가입 가능합니다.");
        }
        System.out.println("가입 성공!");
    }
}
```

### 3-4. 사용자 정의 예외 (Custom Exception)
* 개발자가 직접 만드는 예외

``` java
// 사용자 정의 예외 클래스
class InvalidAgeException extends Exception {
    public InvalidAgeException(String message) {
        super(message);
    }
}

public class CustomExceptionExample {
    public static void main(String[] args) {
        try {
            checkAge(15);
        } catch (InvalidAgeException e) {
            System.out.println("예외 발생: " + e.getMessage());
        }
    }

    public static void checkAge(int age) throws InvalidAgeException {
        if (age < 18) {
            throw new InvalidAgeException("18세 이상만 가입 가능합니다.");
        }
        System.out.println("가입 성공!");
    }
}
```
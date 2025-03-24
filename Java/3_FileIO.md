# Java 파일 입출력

### 1. 파일 입출력의 기본 개념
기본적으로 `java.io.*`를 import하여 사용한다.
``` java
import java.io.* ;
```
1. 쓰기(Write & Save) : `FileWriter`, `BufferedWriter`
2. 읽기(Read & Load) : `FileReader` , `BufferedReader`

### 2. 파일 저장
### 2-1. FileWriter
``` java 
import java.io.* ;

public class FileWriteEX {
    public static void main(String[] args){
        try {
            FileWriter writer = new FileWriter("test.txt") ; // "test.txt"라는 파일 생성
            writer.write("Hello World!"); //파일에 문자열 쓰기
            writer.close(); //파일 닫기
        }
        catch (IOException e){
            System.outprintln(e.getMessage()); //오류 코드 출력
        }
    }
}
```

### 2-2. BufferedWriter (더 효율적임)
`FileWriter`와 달리 `BufferedWriter`은 버터를 사용하여 한번에 데이터를 저장한다.
``` java 
import java.io.*
public class BufferedFileWrite {
    public static void main(String[] args) {
        try (BufferedWriter writer = new BufferedWriter(new FileWriter("test.txt"))) { 
            writer.write("첫 번째 줄\n");
            writer.write("두 번째 줄\n");
        } 
        catch (IOException e) {
            System.out.println( e.getMessage());
        }
    }
}
```
문법적인 차이가 있음을 알수있다.
`BufferedWriter`의 선언 위치를 잘 확인해보길 바란다.

### 3.파일 읽기
### 3-1. FileReader
```java
import java.io.*

public class FileReadEx {
    public static void main(String[] args) {
        try {
            FileReader reader = new FileReader("test.txt");  // 파일 열기
            int ch;
            while ((ch = reader.read()) != -1) {  // 한 글자씩 읽기
                System.out.print((char) ch);
            }
            reader.close();  // 파일 닫기
        } catch (IOException e) {
            System.out.println(e.getMessage());
        }
    }
}
```
`FileRead`을 생성해 파일을 열고, `reader.read()`로 한글자씩 읽을 수 있다.
`while((ch = reader.read()) != -1 )`의 경우 `-1`은 EOF를 의미한다.
이후 읽은 내용을 출력하려면 Type casting을 해주어야한다.

### 3-2. BufferedReader 
``` java
import java.io.*

public class BufferedFileRead {
    public static void main(String[] args) {
        try (BufferedReader reader = new BufferedReader(new FileReader("test.txt"))) {
            String line;
            while ((line = reader.readLine()) != null) {  // 한 줄씩 읽기
                System.out.println(line);
            }
        } catch (IOException e) {
            System.out.println(e.getMessage());
        }
    }
}
```
파일 저장 때와 같이 `BufferedReader`의 선언부 위치에 주의하자.
`reader.readLine()`은 한줄씩 읽기이다. 위에 한글자씩 읽는거보다 빠르겠지 ?

### 4. 파일 경로 설정
```java
String FILE_PATH = "여기에 경로를 입력하세요"
```
파일 경로의 설정의 경우 사용자의 OS에 따라 디렉토리 구조가 다르므로 주의하여야한다.
다행히도 OS에 따라 자동으로 경로를 설정해주는 명령어가 있다 !
```java
// OS에 따라 자동으로 경로 결정
String FILE_PATH = System.getProperty("user.home") + "하위경로" ;
```

### 5. 파일을 특정 양식에 맞게 저장하고 읽기 !
예시로 `이름,승리,무승부,패배`에 맞춰서 저장해보자.
`,`로 구분하는 형식은 `CSV`형식이다.
``` java
class Player {
    String name;
    int win, drew, lose ;

    public Player(String name, int win , int drew, int lose) {
        this.name = name ;
        this.win = win;
        this.drew = drew;
        this.lose = lose;
    }
    // 파일 저장을 위한 CSV로 전환
    public String toCSV() {
        return name + "," + win + "," + drew + "," + lose ;
    }

    //파일 불러오기를 위한 CSV 문자열을 Player 객체로 변환 
     public static Player fromCSV(String line) {
        String[] parts = line.split(",");
        return new Player(
            parts[0],  //이름
            Integer.parseInt(parts[1]), //승리
            Integer.parseInt(parts[2]), //무승부
            Integer.parseInt(parts[3]) //패배
        );
    }
}
```
저장하는거야 우리가 쉼표로 구분해서 저장하면 되는거지만... 불러오는 파트를 확인해보자 !
우선 `,`를 기준으로 데이터가 구분되어 있기 때문에 `split(",")`을 이용해 `,`를 기준으로 나누어 준다.
이를 통해 `,`를 기준으로 문자열 0,1,2 ... 요소에 차례로 저장된다.
이후 형전환을 통해 데이터의 자료형을 의도에 맞게 고쳐주자 !

### 6. java.io.* 의 자주사용하는 메서드들
- `File` 클래스
``` java 
file.exists(); // 파일의 존재 여부 확인
file.length(); //파일의 크기를 바이트 단위로 확인
file.getAbsolutePath(); //파일의 절대경로 확인
file.delete(); //파일 삭제
file.createNewFile(); //파일 생성
```

-`FileWriter` , `BufferedWriter` 클래스
``` java 
write(String text); //문자열을 파일에 씀
newLine(); //줄바꿈
flush(); //버퍼 강제 저장
close(); //파일 닫기
```

-`FileReader` , `BufferedReader` 클래스
``` java 
readLine(); //한 줄씩 읽기 (null 이면 끝)
read(); //한 글자씩 읽기
close(); //파일 닫기
```
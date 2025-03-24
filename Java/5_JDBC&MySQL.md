# JDBC & MySQL 연동
### 1. Java Database Connectivity
자바에서 데이터베이스(MySQL, Oracle 등)에 연결하고 SQL을 실행할 수 있도록 하는 API이다.
- JDBC의 주요 클래스
    - `DriverManager` : DB 연결을 담당
    - `Connection` : DB와의 연결을 나타냄
    - `Statement`,`PreparedStatement` : SQL 실행
    - `ResultSet` : SQL 조회 결과 저장
- JDBC 연동 기본 흐름
    1. MySQL JDBC 드라이버 로드 : `Class.forName("com.mysql.cj.jdbc.Driver")`
    2. DB 연결 생성 : `DriverManager.getConnection(...)`
    3. SQL 실행을 위한 `Statement`, `PreparedStatement` 생성
    4. SQL 실행 후 결과 가져오기 : `ResultSet`
    5. 자원 해제 : `close()`

### 2. 실습코드
0. 하위 폴더 `./lib`에 `mysql-connector-java-9.2.0.jar`파일이 있어야한다.

1. 터미널에서 MySQL DB 생성
``` sql
//로그인
mysql -u root -p

//데이터베이스 선택
CREATE DATABASE testdb;
USE testdb;

//테이블 생성
CREATE TABLE users(
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(100),
    email VARCHAR(100) UNIQUE
);

//테이블 확인
SHOW TABLES;

// 다음과 같이 users table이 만들어 졌다면 성공 
+------------------+
| Tables_in_testdb |
+------------------+
| users            |
+------------------+
1 row in set (0.00 sec)
```
2. JDBCExample.java
```java
import java.sql.*;

public class JDBCExample {
    public static void main(String[] args) {
        // 1. MySQL 연결 정보 설정
        String url = "jdbc:mysql://Junoui-MacBookAir.local:3306/testdb"; // 데이터베이스 주소
        String user = "root"; // mySQL 사용자
        String password = "";

        // 2. JDBC 연결 & SQL 실행
        try {
            // 2-1. MySQL JDBC 드라이버 로드
            Class.forName("com.mysql.cj.jdbc.Driver");

            // 2-2. 데이터베이스 연결
            Connection conn = DriverManager.getConnection(url, user, password);
            System.out.println("MySQL 연결 성공");

            // 2-3. SQL 실행 - 데이터 삽입
            String insertSQL = "INSERT INTO users (name, email) VALUES (?, ?) ON DUPLICATE KEY UPDATE name = VALUES(name)";
            PreparedStatement pstmt = conn.prepareStatement(insertSQL);
            pstmt.setString(1, "홍길동");
            pstmt.setString(2, "hong@knu.ac.kr");
            int rowInserted = pstmt.executeUpdate();
            System.out.println("데이터 삽입 완료! (" + rowInserted + " 행 추가)");

            // 2-4. SQL 실행 - 데이터 조회
            String selectSQL = "SELECT * FROM users";
            Statement stmt = conn.createStatement();
            ResultSet rs = stmt.executeQuery(selectSQL);
            System.out.println("사용자 목록: ");
            while (rs.next()) {
                int id = rs.getInt("id");
                String name = rs.getString("name");
                String email = rs.getString("email");
                System.out.println("ID: " + id + ",이름 : " + name + ", 이메일: " + email);
            }

            // 2-5. 자원 해제
            rs.close();
            stmt.close();
            pstmt.close();
            conn.close();
            System.out.println("MySQL 연결 종료");

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
```
- 출력
```
MySQL 연결 성공
데이터 삽입 완료! (1 행 추가)
사용자 목록: 
ID: 1,이름 : 홍길동, 이메일: hong@knu.ac.kr
MySQL 연결 종료
```
- MySQL 확인
``` SQL
mysql> SELECT * FROM users;
+----+-----------+----------------+
| id | name      | email          |
+----+-----------+----------------+
|  1 | 홍길동    | hong@knu.ac.kr |
+----+-----------+----------------+
1 row in set (0.00 sec)
```
정상적으로 추가된 모습이다.

`JDBCExample.java`를 보면 `String insertSQL = "..."`부분을 보자. MySQL명령어를 String으로 저장한 다음 sql 메서드들에 인자로 사용하여 MySQL을 사용하는 모습이다.

### 3. Create, Read, Update, Delete
```java 
import java.sql.*;
import java.util.Scanner;

public class CRUDExample {
    static final String URL = "jdbc:mysql://localhost:3306/testdb";
    static final String USER = "root";
    static final String PASSWORD = "";

    public static void main(String[] args) {
        //MySQL 연결 및 확인
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            System.out.println("JDBC 드라이버 로드 완료 !");

            Connection conn = DriverManager.getConnection(URL, USER, PASSWORD);
            System.out.println("MySQL 연결 성공 !");
            conn.close();

        } catch (ClassNotFoundException e) {
            System.out.println("MySQL 드라이버를 찾을 수 없음 !");
            e.printStackTrace();
        } catch (SQLException e) {
            System.out.println("MySQL 연결 실패!");
            e.printStackTrace();
        }

        try (Scanner scanner = new Scanner(System.in)) {
            while (true) {
                System.out.println("선택하세요.");
                System.out.println("1. 삽입 | 2. 조회 | 3. 수정 | 4. 삭제 | 5. 종료");
                int choice = scanner.nextInt();
                scanner.nextLine(); // 버퍼 비우기

                switch (choice) {
                    case 1:
                        createUser(scanner);
                        break;
                    case 2:
                        readUsers();
                        break;
                    case 3:
                        updateUser(scanner);
                        break;
                    case 4:
                        deleteUser(scanner);
                        break;
                    case 5:
                        System.out.println("프로그램 종료");
                        return;
                    default:
                        System.out.println("잘못된 입력입니다. 다시 선택하세요.");
                }
            }
        }
    }

    private static void createUser(Scanner scanner) {
        System.out.println("이름 입력 : ");
        String name = scanner.nextLine();
        System.out.println("이메일 입력 : ");
        String email = scanner.nextLine();

        String insertSQL = "INSERT INTO users (name, email) VALUES (?, ?) ON DUPLICATE KEY UPDATE name = VALUES(name)";
        try (Connection conn = DriverManager.getConnection(URL, USER, PASSWORD);
                PreparedStatement pstmt = conn.prepareStatement(insertSQL)) {
            pstmt.setString(1, name);
            pstmt.setString(2, email);
            int rowsInserted = pstmt.executeUpdate();
            System.out.println(rowsInserted + "명의 사용자가 추가되었습니다.");
        } catch (SQLException e) {
            System.out.println("데이터 삽입 실패 !");
            e.printStackTrace();
        }

    }

    private static void readUsers() {
        String selectSQL = "SELECT * FROM users";
        try (Connection conn = DriverManager.getConnection(URL, USER, PASSWORD);
                Statement stmt = conn.createStatement();
                ResultSet rs = stmt.executeQuery(selectSQL)) {
            System.out.println("\n 사용자 목록:");
            while (rs.next()) {
                System.out.println(
                        "ID: " + rs.getInt("id") + ", 이름: " + rs.getString("name") + ", 이메일: " + rs.getString("email"));
            }
        } catch (SQLException e) {
            System.out.println("데이터 조회 실패!");
            e.printStackTrace();
        }
    }

    private static void updateUser(Scanner scanner) {
        System.out.print("수정할 사용자 ID 입력: ");
        int id = scanner.nextInt();
        scanner.nextLine(); // 버퍼 비우기
        System.out.print("새 이름 입력: ");
        String newName = scanner.nextLine();

        String updateSQL = "UPDATE users SET name = ? WHERE id = ?";
        try (Connection conn = DriverManager.getConnection(URL, USER, PASSWORD);
                PreparedStatement pstmt = conn.prepareStatement(updateSQL)) {
            pstmt.setString(1, newName);
            pstmt.setInt(2, id);
            int rowsUpdated = pstmt.executeUpdate();
            if (rowsUpdated > 0) {
                System.out.println("사용자 정보가 업데이트되었습니다.");
            } else {
                System.out.println("해당 ID의 사용자가 없습니다.");
            }
        } catch (SQLException e) {
            System.out.println("데이터 수정 실패!");
            e.printStackTrace();
        }
    }

    private static void deleteUser(Scanner scanner) {
        System.out.print("삭제할 사용자 ID 입력: ");
        int id = scanner.nextInt();

        String deleteSQL = "DELETE FROM users WHERE id = ?";
        try (Connection conn = DriverManager.getConnection(URL, USER, PASSWORD);
                PreparedStatement pstmt = conn.prepareStatement(deleteSQL)) {
            pstmt.setInt(1, id);
            int rowsDeleted = pstmt.executeUpdate();
            if (rowsDeleted > 0) {
                System.out.println("사용자 삭제 완료!");
            } else {
                System.out.println("해당 ID의 사용자가 없습니다.");
            }
        } catch (SQLException e) {
            System.out.println("데이터 삭제 실패!");
            e.printStackTrace();
        }
    }
}
```

- 출력 예시
``` bash 
JDBC 드라이버 로드 완료 !
MySQL 연결 성공 !
선택하세요.
1. 삽입 | 2. 조회 | 3. 수정 | 4. 삭제 | 5. 종료
>> 1
이름 입력 : 
문준호
이메일 입력 : 
bublman3375@knu.ac.kr
1명의 사용자가 추가되었습니다.
선택하세요.
1. 삽입 | 2. 조회 | 3. 수정 | 4. 삭제 | 5. 종료
>> 2

 사용자 목록:
ID: 1, 이름: 홍길동, 이메일: hong@knu.ac.kr
ID: 4, 이름: 문준호, 이메일: bublman3375@knu.ac.kr
선택하세요.
1. 삽입 | 2. 조회 | 3. 수정 | 4. 삭제 | 5. 종료
>> 5
프로그램 종료
```
``` SQL
mysql> SELECT * FROM users;
+----+-----------+-----------------------+
| id | name      | email                 |
+----+-----------+-----------------------+
|  1 | 홍길동    | hong@knu.ac.kr        |
|  4 | 문준호    | bublman3375@knu.ac.kr |
|  5 | 홍명보    | Soccer@korea.com      |
+----+-----------+-----------------------+
3 rows in set (0.01 sec)
```
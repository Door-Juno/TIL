# REST API 설계

상태: 완료
담당자: 문준호
작성일: 05/10/2025
유형: API

# REST API 설계

## 1. REST API 란 ?

REST (Representational State Transfer)는 웹에서 자원을 정의하고 자원에 대한 주소를 지정하는 방식이다.

- URL로 자원(Resource)을 표현한다.
- HTTP 메서드로 행의 정의 : GET(조회) , POST(생성) , PUT(수정) , DELETE(삭제)

### REST 설계 원칙

| 개념 | 예시 |
| --- | --- |
| 자원(Resource)은 명사 | /users, /posts |
| 행위는 HTTP Method로 표현 | GET /users, POST /users … |
| URL는 계층 구조 | /users/1/posts/5 |
| 응답 포맷은 보통 JSON | {”id”:1, “name”:”test” |

## 2. Spring Boot REST API 기본 구조

예제로 todo 관리 서비스를 개발하여보자.

### 1. domain /Todo.java→ 도메인 모델

```java

@Entity
public class Todo {

    @Id @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    private String content;

    private boolean completed;
}
```

- `@Entity`  : 이 클래스는 JPA에서 관리되는 테이블과 매핑된다.
- `@Id` : 이 필드가 Primary Key 임을 나타낸다.
- `@GeneratedValue(strategy = GenerationType.IDENTITY)`  : id는 자동증가한다. MySQL의 `AUTO_INCREMENT` 와 동일한 기능이다.

### 2. repository/TodoRepository.java → DB 접근 계층

```java
public interface TodoRepository extends JpaRepository<Todo, Long> {
}
```

- `JpaRepository<Todo, Long>`  상속
    - 제네릭 1 : 관리할 Entity 타입 (Todo)
    - 제네릭 2 : ID 타입 (Long)
- Spring Data JPA가 자동으로 CRUD 메서드( `findAll` , `save` , `deleteById` , `findbyId` 등을 구현한다.)
- Repository는 DB와의 인터페이스 역할을 하며, 실제 SQL없이도 메서드 이름만으로 동작한다.

### 3. service/TodoService.java → 비지니스 로직 계층

```java
@Service
@RequiredArgsConstructor
public class TodoService {
    private final TodoRepository todoRepository;

    public List<Todo> findAll() {
        return todoRepository.findAll();
    }

    public Todo save(Todo todo) {
        return todoRepository.save(todo);
    }

    public void delete(Long id) {
        todoRepository.deleteById(id);
    }

    public Todo update(Long id, Todo todo) {
        Todo t = todoRepository.findById(id).orElseThrow();
        t.setContent(todo.getContent());
        t.setCompleted(todo.isCompleted());
        return todoRepository.save(t);
    }
}
```

- `@Service` : 이 클래스가 서비스 계층임을 알린다.
- `@RequiredArgsConstructor` : final 필드를 자동으로 생성자 주입한다. 즉, `TodoRepository` 는 자동 주입 된다.
- `update(id,todo)` 설명
    1. ID로 기존 todo를 찾는다. ( `findById(id)` )
    2. 내용을 변경한다. ( `setContent` , `setCompleted`)
    3. 다시 저장한다. (`save`)
- 이 계층은 순수한 로직만을 수행하며, 컨트롤러나 DB 관련 코드를 신경 쓰지 않는다.

### 4. controller/TodoController.java → REST API 요청 처리

```java
@RestController
@RequestMapping("/api/todos")
@RequiredArgsConstructor
public class TodoController {

    private final TodoService todoService;

    @GetMapping
    public List<Todo> getAllTodos() {
        return todoService.findAll();
    }

    @PostMapping
    public Todo createTodo(@RequestBody Todo todo) {
        return todoService.save(todo);
    }

    @PutMapping("/{id}")
    public Todo updateTodo(@PathVariable Long id, @RequestBody Todo todo) {
        return todoService.update(id, todo);
    }

    @DeleteMapping("/{id}")
    public void deleteTodo(@PathVariable Long id) {
        todoService.delete(id);
    }
}
```

- `@RestController`  : JSON 형태로 응답하는 REST 컨트롤러임을 지시한다.
- `@RequestMapping("/api/todos")` : 이 클래스의 모든 메서드는 `/api/todos` 로 시작한다.
- `@GetMapping` , `@PostMapping` 등 .. : GET, POST, PUT, DELETE 등을 지시한다.
    - `@RequestBody` : 요청 JSON을 Todo 객체로 변환한다. / 수정할 데이터
    - `@PathVariable Long id` : URL 경로에서 ID를 추출한다.

## 3. API 테스트하기

### 1. 전체 TODO 조회

- Request

```markdown
GET http://localhost:8080/api/todos
```

- Response

```json
[
  {
    "id": 1,
    "content": "Spring 공부",
    "completed": false
  },
  {
    "id": 2,
    "content": "운동하기",
    "completed": true
  }
]
```

### 2. TODO 추가

- Request

```markdown
POST http://localhost:8080/api/todos
Content-Type: application/json

{
  "content": "REST API 공부",
  "completed": false
}
```

- Response

```json
{
  "id": 3,
  "content": "REST API 공부",
  "completed": false
}
```

- `@RequestBody` 가 JSON → Java 객체(Todo)로 매핑된다.

### 3. TODO 수정

- Request

```markdown
PUT http://localhost:8080/api/todos/3
Content-Type: application/json

{
  "content": "REST API 마스터하기",
  "completed": true
}
```

- Response

```json
{
  "id": 3,
  "content": "REST API 마스터하기",
  "completed": true
}
```

- `@PathVariable` 로 URL의 id값을 받고, `@RequestBody` 로 내용을 업데이트 한다.

### 4. TODO 삭제

- Request

```markdown
DELETE http://localhost:8080/api/todos/3
```

- Response

```json
204 No Content
```

## 마무리하며

이번 글에서는 REST API에 대해 알아보고 Spring boot 를 통해 직접 설계해보고 테스트 해보았다.
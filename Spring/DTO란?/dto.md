## 1. DTO 란 무엇인가 ?

DTO (Data Transfer Object)는 계층 간 데이터 전달을 위해 사용하는 **순수 데이터 객체 이다.**

- Controller ↔ Service ↔ Repository 계층을 오갈때
- 백엔드 ↔ 프론트엔드 사이를 오갈때

불필요한 로직 없이 필요한 필드만 담아서 전달할 때 사용된다.

## 2. DTO를 사용하는 이유

엔티티를 그대로 사용하게 되면 엔티티 객체 그대로를 넘기게 되므로 문제가 야기된다.

1. 엔티티를 그대로 넘기게 되므로 개인 정보(비밀번호)등이 포함된 정보가 넘어가게 된다.
2. 프론트가 필요한 데이터보다 더 많은 필드가 노출된다.
3. API응답 포맷이 바뀌면 엔티티 자체가 영향을 받게된다. → 유연한 확장에 불리하다.

DTO를 사용하면 위와 같은 문제들이 해결되고 다음과 같은 장점을이 생긴다.

1. 역할 분리 : DB 객체와 API 응답 객체를 명확히 구분한다.
2. 보안 강화 : 필요한 정보만 노출할 수 있다.
3. 유지 보수성 향상 : 프론트 요구에 따라 DTO만 수정하면 된다.

## 3. DTO 사용 예시

```java
// Entity (JPA)
@Entity
public class Post {
    @Id
    private Long id;
    private String title;
    private String content;
    private String author;
    private LocalDateTime createdAt;
}
```

```java
// DTO (클라이언트 응답용)
public class PostResponseDto {
    private String title;
    private String content;

    public PostResponseDto(Post post) {
        this.title = post.getTitle();
        this.content = post.getContent();
    }
}
```

- Post 타입 객체 post의 JPA 메서드들을 활용하여 `title` 과 `content` 만을 가져오고 있다.

## 4. DTO 의 종류

### Request DTO

클라이언트가 보낸 요청 데이터를 받기 위한 객체. 
클라이언트 → 서버로 전달되는 Request 데이터를 담는 객체이다.

```java
public class PostRequestDto {
    @NotBlank
    private String title;

    @NotBlank
    private String content;
}
```

```java
// Controller
@PostMapping("/posts")
public ResponseEntity<?> createPost(@RequestBody @Valid PostRequestDto requestDto) {
    // 요청 처리 로직 (주로 Service 호출)
}
```

- `@RequestBody` 와 함께 사용
- 클라이언트가 보낸 JSON → Java 객체로 매핑된다.
- 유효성 검사용으로 자주 사용된다. (`@NotBlank`, `@Email` 등)

### Response DTO

서버 → 클라이언트로 전달하는 Response 데이터를 담는 객체이다.

```java
public class PostResponseDto {
    private String title;
    private String content;
}
```

```java
// Controller
@GetMapping("/posts/{id}")
public PostResponseDto getPost(@PathVariable Long id) {
    Post post = postService.findById(id);
    return new PostResponseDto(post);
}
```

- 응답에 필요한 정보만 선택적으로 포함
- 엔티티를 보내는 대신, 가공된 형태로 반환한다.
- 보안 / 응답 포맷 유지를 위해 중요하다.

## 5. DTO 와 Lombok

- Lombok을 쓰면 어노테이션을 활용하여 코드가 간결해진다.
- `MapStruct` , `ModelMapper` 과 같은 라이브러리로 Entity ↔ DTO 변환 자동화도 가능하다.
- 엔티티와 완전히 1:1 매핑하지 않아도 된다.

## 6. 마무리하며

DTO는 계층 간 의존도를 줄이고, 보안과 유지보수성을 높여주는 중요한 개념이다.
DTO를 적극 활용하여 유연하고 안정적인 API 설계가 가능해진다.

추가적으로, Request DTO는 클라이언트 입력 검증이 핵심이고, Response DTO는 노출해서는 안 될 데이터를 숨기는게 핵심이다.
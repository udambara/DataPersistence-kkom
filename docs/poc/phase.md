# DataPersistence 구현 계획

1. Sample / Order 데이터 모델 및 JSON 스키마 설계
2. JSON 파일 read/write 기본 유틸 구현
3. Sample CRUD 구현 - 등록, 전체조회(재고 포함), 이름 등 속성 검색
4. Order CRUD 구현 - 생성(예약), 상태별 조회·필터링, 상태 변경(승인/거절/생산완료/출고)
5. 재고 증감 로직 구현 - 생산 완료 시 재고 증가, 출고 시 재고 차감

## PoC-1 범위 (2026-07-15 확정)
- 실제 구현: Sample 엔티티 + SampleRepository(Add/GetAll/FindByName, ID 중복 검사), Order 엔티티 + OrderRepository(Add/GetAll/상태별 건수 집계)
- JSON은 nlohmann/json 단일 헤더 벤더링 사용
- 재고 증감 로직(생산완료/출고 연동)은 이번 범위 제외 (생산라인/출고처리 미구현이므로)

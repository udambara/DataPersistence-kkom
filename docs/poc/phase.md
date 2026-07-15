# DataPersistence 구현 계획

1. Sample / Order 데이터 모델 및 JSON 스키마 설계
2. JSON 파일 read/write 기본 유틸 구현
3. Sample CRUD 구현 - 등록, 전체조회(재고 포함), 이름 등 속성 검색
4. Order CRUD 구현 - 생성(예약), 상태별 조회·필터링, 상태 변경(승인/거절/생산완료/출고)
5. 재고 증감 로직 구현 - 생산 완료 시 재고 증가, 출고 시 재고 차감

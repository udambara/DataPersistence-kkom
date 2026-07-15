# DataPersistence PRD

## 개요
시료(Sample)와 주문(Order) 데이터를 JSON 파일로 영속화하는 계층.

## 요구사항
- Sample : 시료ID, 이름, 평균생산시간, 수율, 재고수량 저장
- Order : 주문ID, 시료ID, 고객명, 주문수량, 상태(RESERVED / CONFIRMED / PRODUCING / RELEASE / REJECTED) 저장
- Sample CRUD : 등록 / 전체조회(재고 포함) / 이름 등 속성 검색
- Order CRUD : 생성(예약) / 상태 조회·필터링(상태별) / 상태 변경(승인·거절·생산완료·출고)
- 재고 수량 증감(생산 완료 시 증가, 출고 시 차감) 반영
- JSON 파일 read/write 시 데이터 정합성 유지 (동시성은 고려하지 않음, 단일 프로세스 기준)

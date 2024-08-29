# Tiểu luận môn Lập trình IoT: Đề tài Platform Mainflux

## Các thành viên làm tiểu luận:
- Nguyễn Trọng Hiếu
- Phạm Hoàng Phương

## Hướng dẫn sử dụng:
Phần mềm cần thiết để chạy tiểu luận:
- Docker Desktop.
- Docker Compose.
- Arduino IDE. (Để nạp code cho ESP8266).

### Bước 1: Chuẩn bị môi trường
- Vào thư mục `mainflux-0.21.0`.
- Mở CMD, Git Bash, hoặc Terminal tại thư mục này.

### Bước 2: Build và chạy Docker Compose
- Gõ lệnh sau để build các container, image, và volume trong Docker:
  ```bash
  docker compose -f "docker-compose.yml" up -d --build
### Bước 3: Khôi phục dữ liệu cho các volume
docker run --rm -v docker_mainfluxlabs-mqtt-db-volume:/volume -v /d/backups:/backup alpine sh -c "tar -xzvf /backup/docker_mainfluxlabs-mqtt-db-volume.tar.gz -C /volume"
docker run --rm -v docker_grafana_data:/volume -v /d/backups:/backup alpine sh -c "tar -xzvf /backup/docker_grafana_data.tar.gz -C /volume"
nhớ coppy thư mục backups đem vào ổ d
### Bước 2: Build và chạy Docker Compose
Khi chạy dự án sử dụng: localhost:3001 dể có thể vào giao diện của grafana để kết nối cơ sở dữ liệu: mqtt-db của Mainflux trong phần Data source. Tiến hành tạo dashboard để có thể show dữ liệu.

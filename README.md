Tiểu luận môn lập trình IOT: Đề tài platform Mainflux
Các thành viên làm tiểu luận:
Nguyễn Trọng Hiếu
Phạm Hoàng Phương
Hướng dãn sử dụng:
phần mềm cany2 có để chạy tiểu luận:
Docker Desktop.
Docker compose.
Arduino IDE. (Để chạy nạp code 8266).
vào thư mục mainflux-0.21.0
tại đường dẫn của thư mục này ta tiến hành mở (CMD Hoặc Git Bash hoạc terminal) để gõ: docker compose -f "docker-compose.yml" up -d --build lệnh này dùng để build các: Container ,image và volume trong docker.
Sau khi chạy xong lệnh docker compose tiến hành chạy tiếp hai lệnh:
docker run --rm -v docker_mainfluxlabs-mqtt-db-volume:/volume -v /d/backups:/backup alpine sh -c "tar -xzvf /backup/docker_mainfluxlabs-mqtt-db-volume.tar.gz -C /volume"
docker run --rm -v docker_grafana_data:/volume -v /d/backups:/backup alpine sh -c "tar -xzvf /backup/docker_grafana_data.tar.gz -C /volume"
nhớ coppy thư mục backups đem vào ổ d
Khi chạy dự án sử dụng: localhost:3001 dể có thể vào giao diện của grafana để kết nối cơ sở dữ liệu: mqtt-db của Mainflux trong phần Data source. Tiến hành tạo dashboard để có thể show dữ liệu.

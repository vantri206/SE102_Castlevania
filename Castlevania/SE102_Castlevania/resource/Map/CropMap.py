from PIL import Image, ImageDraw
import os
import numpy as np
import tkinter as tk
from tkinter import filedialog

def slice_map(image_path, tile_width, tile_height, output_image, matrix_output):

    # Mở ảnh bản đồ từ file đã chọn
    image = Image.open(image_path).convert("RGBA")
    draw = ImageDraw.Draw(image)
    image_width, image_height = image.size

    unique_tiles = []
    seen_tiles_data = {}
    tile_matrix = []

    # Cắt ảnh thành các tile và gán ID
    for y in range(0, image_height, tile_height):
        row = []
        for x in range(0, image_width, tile_width):
            tile = image.crop((x, y, x + tile_width, y + tile_height))
            tile_data = tile.tobytes()  # Chuyển tile thành bytes để so sánh

            if tile_data not in seen_tiles_data:
                tile_id = len(unique_tiles)
                seen_tiles_data[tile_data] = tile_id
                unique_tiles.append(tile)
            else:
                tile_id = seen_tiles_data[tile_data]

            row.append(tile_id)
        tile_matrix.append(row)
    # Vẽ đường cắt lên ảnh gốc
    for y in range(0, image_height, tile_height):
        draw.line([(0, y), (image_width, y)], fill="red", width=1)
    for x in range(0, image_width, tile_width):
        draw.line([(x, 0), (x, image_height)], fill="red", width=1)

    #image.save("map_with_grid.png")
    #print("Đã lưu ảnh gốc với đường cắt: map_with_grid.png")

    # Sắp xếp và ghép các tile vào một ảnh duy nhất
    unique_count = len(unique_tiles)
    columns = int(unique_count ** 0.5) + 1
    rows = (unique_count // columns) + (1 if unique_count % columns else 0)
    output_width = columns * tile_width
    output_height = rows * tile_height

    output_image_obj = Image.new("RGBA", (output_width, output_height))

    for index, tile in enumerate(unique_tiles):
        x = (index % columns) * tile_width
        y = (index // columns) * tile_height
        output_image_obj.paste(tile, (x, y))

    output_image_obj.save(output_image)
    print(f"Đã tạo ảnh chứa {unique_count} tile duy nhất: {output_image}")

    # Lưu ma trận vào file
    # Tính số hàng và số cột của ma trận tile
    matrix_rows = len(tile_matrix)
    matrix_cols = len(tile_matrix[0]) if tile_matrix else 0

    # Ghi thông tin vào file txt
    with open(matrix_output, 'w') as f:
        # Dòng 1: Kích thước của map gốc (pixel x pixel)
        f.write(f"{image_width} {image_height} # Map size\n")
        # Dòng 2: Kích thước của tile (width, height)
        f.write(f"{tile_width} {tile_height} # Tile size\n")
        # Dòng 3: Số hàng và số cột của map
        f.write(f"{matrix_cols} {matrix_rows} # Matrix size\n")
        # Dòng 4: Số tile độc nhất
        f.write(f"{unique_count} # Unique tiles\n")
        # Dòng 5: Số hàng và số cột của unique tiles
        f.write(f"{columns} x {rows} # Unique tiles grid\n")
        # Ghi ma trận ID
        np.savetxt(f, np.array(tile_matrix, dtype=int), fmt="%d")
        print(f"Đã lưu ma trận tile vào file: {matrix_output}")

# Tạo cửa sổ ẩn và mở dialog chọn file
'''root = tk.Tk()
root.withdraw()  # Ẩn cửa sổ chính
image_path = filedialog.askopenfilename(
    title="Chọn file ảnh bản đồ",
    filetypes=[("Image files", "*.png *.jpg *.jpeg *.bmp *.gif")]
)

if not image_path:  # Nếu người dùng không chọn file
    print("Không có file nào được chọn!")
    exit()'''
# Sử dụng hàm
for i in range(1, 6):
    image_path = f"Stage{i}.png"
    slice_map(image_path, 16, 16, f"Stage{i}_tiles.png", f"Stage{i}.txt")
from graphviz import Digraph

# Tạo đồ thị trạng thái
dot = Digraph(comment="State Diagram of Simon Belmont in Castlevania")
dot.attr(rankdir="LR")  # Hiển thị từ trái sang phải
dot.attr(size="15,10!")  # Kích thước lớn hơn (15x10 inch)
dot.attr(dpi="300")     # Độ phân giải cao

# Danh sách trạng thái
states = [
    "IDLE", "WALKING", "JUMPING", "ATTACKING", "CROUCHING",
    "CLIMBING STAIRS", "USING SUB-WEAPON", "TAKING DAMAGE",
    "DYING", "GAME OVER"
]

# Định dạng các node
for state in states:
    dot.node(state, state, shape="ellipse", style="filled", fillcolor="lightblue")

# Thêm các cạnh với điều kiện chuyển đổi (đã chỉnh sửa để tất cả đi qua IDLE)
transitions = [
    # Từ IDLE có thể chuyển sang các trạng thái khác
    ("IDLE", "WALKING", "Press left/right"),
    ("IDLE", "JUMPING", "Press X"),
    ("IDLE", "CROUCHING", "Press down"),
    ("IDLE", "ATTACKING", "Press Z"),
    ("IDLE", "TAKING DAMAGE", "Get hit"),
    ("IDLE", "CLIMBING STAIRS", "Near stairs + press up/down"),
    ("IDLE", "USING SUB-WEAPON", "Press C"),

    # Từ WALKING chỉ có thể quay về IDLE hoặc bị tổn thương
    ("WALKING", "IDLE", "Release left/right"),
    ("WALKING", "TAKING DAMAGE", "Get hit"),

    # Từ JUMPING chỉ có thể quay về IDLE hoặc bị tổn thương
    ("JUMPING", "IDLE", "Land"),
    ("JUMPING", "TAKING DAMAGE", "Get hit"),

    # Từ ATTACKING chỉ có thể quay về IDLE hoặc bị tổn thương
    ("ATTACKING", "IDLE", "Attack ends"),
    ("ATTACKING", "TAKING DAMAGE", "Get hit"),

    # Từ CROUCHING chỉ có thể quay về IDLE hoặc bị tổn thương
    ("CROUCHING", "IDLE", "Release down"),
    ("CROUCHING", "TAKING DAMAGE", "Get hit"),

    # Từ CLIMBING STAIRS chỉ có thể quay về IDLE hoặc bị tổn thương
    ("CLIMBING STAIRS", "IDLE", "Reach stair end"),
    ("CLIMBING STAIRS", "TAKING DAMAGE", "Get hit"),

    # Từ USING SUB-WEAPON chỉ có thể quay về IDLE hoặc bị tổn thương
    ("USING SUB-WEAPON", "IDLE", "Action ends"),
    ("USING SUB-WEAPON", "TAKING DAMAGE", "Get hit"),

    # Từ TAKING DAMAGE có thể quay về IDLE hoặc dẫn đến DYING
    ("TAKING DAMAGE", "IDLE", "Animation ends"),
    ("TAKING DAMAGE", "DYING", "Health depleted"),

    # Từ DYING có thể dẫn đến GAME OVER hoặc quay về IDLE (nếu còn mạng)
    ("DYING", "GAME OVER", "No lives left"),
    ("DYING", "IDLE", "Lives remain (checkpoint)"),
]

# Thêm cạnh vào đồ thị
for src, dst, label in transitions:
    dot.edge(src, dst, label=label, color="gray", fontcolor="red", fontsize="10")

# Hiển thị và lưu đồ thị
dot.render("state_diagram", format="png", view=True)  # Lưu thành PNG
dot.render("state_diagram", format="svg")  # Lưu thành SVG
print("Diagram created and saved as 'state_diagram.png' and 'state_diagram.svg'")
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

# Thêm các cạnh với điều kiện chuyển đổi (đã chỉnh sửa)
transitions = [
    ("IDLE", "WALKING", "Press left/right"),
    ("IDLE", "JUMPING", "Press X"),
    ("IDLE", "CROUCHING", "Press down"),
    ("IDLE", "ATTACKING", "Press Z"),
    ("IDLE", "TAKING DAMAGE", "Get hit"),
    ("IDLE", "CLIMBING STAIRS", "Near stairs + press up/down"),
    ("IDLE", "USING SUB-WEAPON", "Press C"),

    ("WALKING", "IDLE", "Release left/right"),
    ("WALKING", "JUMPING", "Press X"),
    ("WALKING", "ATTACKING", "Press Z"),
    ("WALKING", "TAKING DAMAGE", "Get hit"),
    ("WALKING", "CLIMBING STAIRS", "Near stairs + press up/down"),
    ("WALKING", "USING SUB-WEAPON", "Press C"),

    ("JUMPING", "IDLE", "Land"),
    ("JUMPING", "WALKING", "Land + hold left/right"),
    ("JUMPING", "ATTACKING", "Press Z"),
    ("JUMPING", "TAKING DAMAGE", "Get hit"),

    ("ATTACKING", "IDLE", "Attack ends"),
    ("ATTACKING", "WALKING", "Attack ends + hold left/right"),
    ("ATTACKING", "CROUCHING", "Attack ends + press down"),
    ("ATTACKING", "TAKING DAMAGE", "Get hit"),
    # Không còn "ATTACKING" -> "USING SUB-WEAPON" trực tiếp

    ("CROUCHING", "IDLE", "Release down"),
    ("CROUCHING", "ATTACKING", "Press Z"),
    ("CROUCHING", "TAKING DAMAGE", "Get hit"),
    ("CROUCHING", "USING SUB-WEAPON", "Press C"),

    ("CLIMBING STAIRS", "IDLE", "Reach stair end"),
    ("CLIMBING STAIRS", "ATTACKING", "Press Z"),
    ("CLIMBING STAIRS", "TAKING DAMAGE", "Get hit"),

    ("USING SUB-WEAPON", "IDLE", "Action ends"),
    ("USING SUB-WEAPON", "WALKING", "Action ends + hold left/right"),
    ("USING SUB-WEAPON", "TAKING DAMAGE", "Get hit"),

    ("TAKING DAMAGE", "IDLE", "Animation ends"),
    ("TAKING DAMAGE", "DYING", "Health depleted"),

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
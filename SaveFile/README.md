Это бибилотека для записи, ведения и сохранения данных. Все здесь представленно в виде словаря.

Для добавления библиотеки к вашему проекту в Cmake:


add_subdirectory(SaveFile)

target_link_libraries("name_exe" PUBLIC SaveLib)

add_dependencies("name_exe" SaveLib)
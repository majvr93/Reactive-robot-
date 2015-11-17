Reactive Robot with ROS



Compilar:
	. devel/setup.bash
	catkin_make --pkg stdr

Iniciar plataforma:
		roslaunch stdr_launchers server_with_map_and_gui_plus_robot.launch

Iniciar algoritmo:
		rosrun stdr stdr_node

Path do código : src/stdr/src/stdr.cpp

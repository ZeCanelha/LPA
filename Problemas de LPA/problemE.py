# Area of Polygon using Shoelace formula
# corners must be ordered in clockwise or counter-clockwise direction
import math
import sys

def main():
	room_coord = []
	cam_coord = []
	#Variavel para os casos de teste
	casos_teste = input()

	for x in range(0, casos_teste):
		
		V, C = map(int, sys.stdin.readline().split())
		#V, C = map(int, raw_input().strip().split(" "))
		for i in range(0, V):	
			x, y = map(float, sys.stdin.readline().split())
			#x, y = map(float, raw_input().strip().split(" "))
			room_coord.append((x, y)) 

		for i in range(0, C):
			x, y, O, A, D = map(float, sys.stdin.readline().split())
			#x, y, O, A, D = map(float, raw_input().strip().split())
			cam_coord.append((x, y, O, A, D))

		#Print da area do quarto
		print("%.8f" % area_of_room(room_coord))
		room_coord = []
		cam_coord = []
	

#Function to calculate the area of the given room
def area_of_room(coord):
    n = len(coord) # of corners
    area = 0.0
    for i in range(n):
        j = (i + 1) % n
        area += coord[i][0] * coord[j][1]
        area -= coord[j][0] * coord[i][1]
    area = abs(area) / 2.0
    return area

# examples
corners1 = [(0.0, 2.0), (2.0, 4.0), (4.0, 2.0), (2.0, 0.0)]
corners2 = [(1.0, 6.0), (3.0, 7.0), (7.0, 7.0), (7.0, 4.0), (6.0, 2.0), (2.0, 1.0)]


if __name__ == '__main__':
	main()
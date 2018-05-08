import numpy as np

################################################################################
######################### jonesjon 932709446 ###################################
################################################################################


#Object that tracks degree and if visited
class Tile:
    degree = 0
    visited = False

#Cartesian coordinate
class Point:
    x = 0
    y = 0

#Initializes a board of Tiles where degree and visited information is stored
def createDegreeMap(n, m):
    board = []
    #Initialize the board
    for i in range(0, n):
        row = []
        for j in range(0, m):
            tile = Tile()
            row.append(tile)
        board.append(row)

    #Set the degree values on the board
    for i in range(0, n):
        for j in range(0, m):
            board[i][j].degree = calculateDegree(board,j,i)
    return board


#Returns the point with the lowest degree from the set of points given
def lowestDegree(board, points):
    #Start lowDeg with a large number
    lowDeg = 1000
    nextPos = Point()

    #For each point in points, check its degree and return the lowest degree
    for point in points:
        tile = board[point.y][point.x]
        if tile.visited == False and tile.degree < lowDeg:
            lowDeg = tile.degree
            nextPos = point
    return nextPos

#Returns an array of points that are possible moves
def getPossibleMoves(board, point):
    n = len(board)
    m = len(board[0])
    i = point.x
    j = point.y
    points = []

    #Check all 8 possible cases
    if ((i + 1) >= 0 and (i + 1) < m) and ((j + 2) >= 0 and (j + 2) < n):
        if not(board[j+2][i+1].visited):
            move = Point()
            move.x = i + 1
            move.y = j + 2
            points.append(move)
    if ((i + 2) >= 0 and (i + 2) < m) and ((j + 1) >= 0 and (j + 1) < n):
        if not(board[j+1][i+2].visited):
            move = Point()
            move.x = i + 2
            move.y = j + 1
            points.append(move)
    if ((i + 2) >= 0 and (i + 2) < m) and ((j - 1) >= 0 and (j - 1) < n):
        if not(board[j-1][i+2].visited):
            move = Point()
            move.x = i + 2
            move.y = j - 1
            points.append(move)
    if ((i + 1) >= 0 and (i + 1) < m) and ((j - 2) >= 0 and (j - 2) < n):
        if not(board[j-2][i+1].visited):
            move = Point()
            move.x = i + 1
            move.y = j - 2
            points.append(move)
    if ((i - 1) >= 0 and (i - 1) < m) and ((j - 2) >= 0 and (j - 2) < n):
        if not(board[j-2][i-1].visited):
            move = Point()
            move.x = i - 1
            move.y = j - 2
            points.append(move)
    if ((i - 2) >= 0 and (i - 2) < m) and ((j - 1) >= 0 and (j - 1) < n):
        if not(board[j-1][i-2].visited):
            move = Point()
            move.x = i - 2
            move.y = j - 1
            points.append(move)
    if ((i - 2) >= 0 and (i - 2) < m) and ((j + 1) >= 0 and (j + 1) < n):
        if not(board[j+1][i-2].visited):
            move = Point()
            move.x = i - 2
            move.y = j + 1
            points.append(move)
    if ((i - 1) >= 0 and (i - 1) < m) and ((j + 2) >= 0 and (j + 2) < n):
        if not(board[j+2][i-1].visited):
            move = Point()
            move.x = i - 1
            move.y = j + 2
            points.append(move)
    return points

#Decrement the degree of the points given by 1
def updateBoard(board, points):
    for point in points:
        board[point.y][point.x].degree -= 1

#Calculate the degree at the given point
def calculateDegree(board, i, j):
    point = Point()
    point.x = i
    point.y = j
    degree = len(getPossibleMoves(board, point))
    return degree

#Returns a chessboard with spots visited and when they were visited
def tour(n, m, i, j):
    start = Point()
    start.x = i
    start.y = j
    currentPos = start
    nextMove = Point()

    counter = 1
    moves = [[0]*n for _ in range(m)]
    moves[start.y][start.x] = counter

    board = createDegreeMap(n, m)
    #Get initial possible moves
    possibleMoves = getPossibleMoves(board, start)
    while len(getPossibleMoves(board, currentPos)) != 0:
        counter += 1
        #Make a move
        nextMove = lowestDegree(board, possibleMoves)
        moves[nextMove.y][nextMove.x] = counter
        board[currentPos.y][currentPos.x].visited = True
        #update board after move
        updateBoard(board, possibleMoves)
        possibleMoves = getPossibleMoves(board, nextMove)
        currentPos = nextMove
    return moves

def foundPath(steps):
    for rowSteps in steps:
        for step in rowSteps:
            if step == 0:
                return False
    return True

def main():
    numFound = 0
    n = input("How many rows?: ")
    m = input("How many columns?: ")
    i = input("Starting x coordinate?: ")
    j = input("Starting y coordinate?: ")

    print "Running program..."

    board = tour(n, m, i, j)
    for row in board:
        print row
    if foundPath(board):
        print "Found a path."
    else:
        print "Failed to find a path."

main()

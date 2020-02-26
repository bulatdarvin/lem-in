import sys
import re
import pygame


ROOM_COLOR = (87, 62, 62)
END_ROOM = (250, 107, 107)
START_ROOM = (84, 0, 0)
LINE_COLOR = (212, 205, 205)

WIDTH = 500
HEIGHT = 500

SIZE = 50

def getLine(x1, y1, x2, y2):
    x1, y1, x2, y2 = int(x1), int(y1), int(x2), int(y2)
    points = []
    issteep = abs(y2-y1) > abs(x2-x1)
    if issteep:
        x1, y1 = y1, x1
        x2, y2 = y2, x2
    rev = False
    if x1 > x2:
        x1, x2 = x2, x1
        y1, y2 = y2, y1
        rev = True
    deltax = x2 - x1
    deltay = abs(y2-y1)
    error = int(deltax / 2)
    y = y1
    ystep = None
    if y1 < y2:
        ystep = 1
    else:
        ystep = -1
    for x in range(x1, x2 + 1):
        if issteep:
            points.append((y, x))
        else:
            points.append((x, y))
        error -= deltay
        if error < 0:
            y += ystep
            error += deltax
    # Reverse the list if the coordinates were reversed
    if rev:
        points.reverse()
    return points

class Ant:
    def __init__(self, name, start):
        self.path = None
        self.name = name
        self.x, self.y = start
        self.img = pygame.image.load(sys.path[0] + "/ant.png").convert_alpha()
        self.move_list = None
        self.ind = 0
    
    def start_ant(self, end):
        self.move_list = getLine(self.x, self.y, end[0], end[1])
        self.move_list.append(end)

    def move(self):
        if self.move_list == None:
            self.ind = 0
            return 0
        self.ind += 1
        print(len(self.move_list))
        if self.ind >= len(self.move_list) - 1:
            self.x, self.y = self.move_list[-1]
            self.move_list = None
            self.ind = 0
            return 0
        else:
            self.x, self.y = self.move_list[self.ind]
            return 1
        


    
class Room:
    def __init__(self, name, coords, roomsize, start_end=0):
        self.name = name
        self.x, self.y = coords
        self.conns = {}
        self.start_end = start_end
        self.disp_x = self.x * SIZE
        self.disp_y = self.y * SIZE
        self.roomsize = roomsize
        self.center = []


class Game:
    
    def __init__(self):
        pygame.init()
        pygame.key.set_repeat(150, 5)
        self.surf = pygame.display.set_mode((WIDTH, HEIGHT), 0, 32)
        self.clock = pygame.time.Clock()
        pygame.display.set_caption("lem-in visualizer\n")
        self.background = pygame.image.load(sys.path[0] + "/background.jpg").convert()
        self.FPS = 60
        self.ants_num = 0
        self.roommap = {}
        self.antmap = {}
        self.roomsize = SIZE
        self.start = None
        self.end = None
        self.moves = []
        self.max_x = None
        self.max_y = None
        self.min_x = None
        self.min_y = None
        self.iteration = 0
        self.moving_ant = 0

    def add_room(self, line, start_end):
        tmp = line.split(" ")
        new = Room(tmp[0], (int(tmp[1]), int(tmp[2])), self.roomsize, start_end)
        if start_end == 1:
            self.start = new
        elif start_end == -1:
            self.end = new
        self.roommap[new.name] = new
        if self.max_x == None or self.max_x < new.disp_x:
            self.max_x = new.disp_x
        if self.max_y == None or self.max_y < new.disp_y:
            self.max_y = new.disp_y
        if self.min_x == None or self.min_x > new.disp_x:
            self.min_x = new.disp_x
        if self.min_y == None or self.min_y > new.disp_y:
            self.min_y = new.disp_y

    def add_conn(self, line):
        tmp = line.split("-")
        try:
            self.roommap[tmp[0]].conns[tmp[1]] = self.roommap[tmp[1]]
            self.roommap[tmp[1]].conns[tmp[0]] = self.roommap[tmp[0]]
        except KeyError:
            print("Error")
    
    def read_input(self):
        file = sys.stdin.read()
        lines = file.split('\n')
        linum = len(lines)
        self.ants_num = int(lines[0])
        n = 1
        start_end = 0
        room_p = re.compile("(?:(?:[a-zA-Z0-9_]+ \d+ \d+$)|(?:^#))")
        while n < linum and room_p.match(lines[n]):
            if (lines[n][0] == '#'):
                if lines[n] == "##start":
                    start_end = 1
                elif lines[n] == "##end":
                    start_end = -1
                n += 1
                continue
            else:
                self.add_room(lines[n], start_end)
                n += 1
                start_end = 0
        connnect_p = re.compile("(?:(?:[a-zA-Z0-9_]+-[a-zA-z0-9_]+$)|(?:^#))")
        while n < linum and connnect_p.match(lines[n]):
            self.add_conn(lines[n])
            n += 1
        n += 1
        move_p = re.compile(("(?:L[0-9]+-[a-zA-Z0-9_]+ ?)+$"))
        while n < linum and move_p.match(lines[n]):
            self.moves.append(lines[n])
            n += 1
        if linum != n + 1:
            print(linum, n)
        for room in self.roommap:
            self.correct_room(self.roommap[room])
        self.moves = [[]] + self.moves
        for ind in range(1, self.ants_num + 1):
            name = "L" + str(ind)
            self.antmap[name] = Ant(name, self.start.center)
    
    def correct_room(self, Room):
        Room.disp_x = Room.disp_x + int(WIDTH / 2) - int((self.max_x - self.min_x) / 2)
        Room.disp_y = Room.disp_y + int(HEIGHT / 2) - int((self.max_y - self.min_y) / 2)
        Room.center = [Room.disp_x + int(Room.roomsize / 2), Room.disp_y + int(Room.roomsize / 2)]


    def draw_rooms(self):
        for room in self.roommap:
            if self.roommap[room].start_end == 1:
                color = START_ROOM
            elif self.roommap[room].start_end == -1:
                color = END_ROOM
            else:
                color = ROOM_COLOR
            pygame.draw.rect(self.surf, color, (self.roommap[room].disp_x, self.roommap[room].disp_y, self.roomsize, self.roomsize))

    def draw_conns(self):
        for rooms in self.roommap:
            room_1 = self.roommap[rooms]
            for tmp in room_1.conns:
                room_2 = self.roommap[tmp]
                pygame.draw.line(self.surf, LINE_COLOR, room_1.center, room_2.center, SIZE // 10)

    def draw_ant(self, ant):
        image = ant.img.get_rect()
        image.center = (ant.x, ant.y)
        self.surf.blit(ant.img, image)
    
    def display_ants(self):
        for ant in self.antmap:
            self.draw_ant(self.antmap[ant])

    def move_preparation(self):
        line = self.moves[self.iteration]
        if line == []:
            return
        lines_arr = [n.split('-') for n in line.split(' ')]
        if len(lines_arr[-1]) == 1:
            del lines_arr[-1]
        print(lines_arr)
        for n in lines_arr:
            if len(n) != 2:
                print("Err")
                #pygame.quit()
            self.antmap[n[0]].start_ant(self.roommap[n[1]].center)

    def move(self):
        for n in self.antmap:
            self.moving_ant += self.antmap[n].move()

    def event(self):
        for i in pygame.event.get():
            if i.type == pygame.QUIT: 
                pygame.quit()
            if i.type == pygame.KEYDOWN:
                if i.key == pygame.K_ESCAPE:
                    pygame.quit()
                if i.key == pygame.K_RIGHT:
                    self.iteration = min(self.iteration + 1, len(self.moves) - 1) 

    def animation(self):
        while 1:
            self.event()
            self.surf.blit(self.background, [0,0])
            #self.surf.blit(Ant.img, [10,10])
            self.draw_conns()
            self.draw_rooms()
            self.display_ants()
            self.move_preparation()
            self.move()
            pygame.display.update()
            self.clock.tick(60)

if __name__ == "__main__":
    g = Game()
    g.read_input()
    g.animation()
    #print("MAP: ")
    #for rooms in g.roommap:
    #    print(rooms)
    pass

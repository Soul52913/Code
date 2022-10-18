from vpython import *
from numpy import *

N = 100
R, lamda = 1.0, 500E-9
d = 100E-6
k = 2 * pi / lamda

dx, dy = d/N, d/N
scene1 = canvas(align = 'left', height=600, width=600, center = vector(N*dx/2, N*dy/2, 0))
scene2 = canvas(align = 'right', x=600, height=600, width=600, center = vector(N*dx/2, N*dy/2, 0))
scene1.lights, scene2.lights = [], []
scene1.ambient, scene2.ambient = color.gray(0.99), color.gray(0.99)
side = linspace(-0.01*pi, 0.01*pi, N)
x,y = meshgrid(side,side)

A = zeros((N, N))
for i in range(N):
    for j in range(N):
        if ((i - 0.5 * N) ** 2 + (j - 0.5 * N) ** 2) <= (0.5 * N) ** 2:
            A += (cos(x * k * (i * dx - d / 2) / R + y * k * (j * dy - d / 2) / R) / R)
E_field = A

Inte = abs(E_field) ** 2
maxI = amax(Inte)
for i in range(N):
    for j in range(N):
        box(canvas = scene1, pos=vector(i*dx, j*dy, 0), length = dx, height= dy, width = dx,
            color=vector(Inte[i,j]/maxI,Inte[i,j]/maxI,Inte[i,j]/maxI))

ii = int(N / 2)
im = Inte[ii][int(N / 2)]
while True:
    if Inte[ii][int(N / 2)] <= im:
        im = Inte[ii][int(N / 2)]
        ii += 1
    else:
        print("simulated Rayleigh criterion", (ii - N / 2) * (0.02 * pi / N))
        break

Inte = abs(E_field)
maxI = amax(Inte)
for i in range(N):
    for j in range(N):
        box(canvas = scene2, pos=vector(i*dx, j*dy, 0), length = dx, height= dy, width = dx,
            color=vector(Inte[i,j]/maxI,Inte[i,j]/maxI,Inte[i,j]/maxI))

print("theoretical Rayleigh criterion", 1.22 * lamda / d)
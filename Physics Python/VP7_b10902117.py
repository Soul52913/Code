from vpython import *

fd = 120 # 120Hz
T = 1 / fd

R = 30
L = 200 * 10**(-3)
C = 20 * 10**(-6)

Q = 0
i = 0
E_total = 0

check = 0
checkV = 0
checkE = 0
i_before = -1
v_before = -1

t = 0
dt = 1.0/(fd * 5000) # 5000 simulation points per cycle

scene1 = graph(align='left', xtitle='t', ytitle='i (A) blue, v (100V) red,', background=vector(0.2, 0.6, 0.2))
scene2 = graph(align='left', xtitle='t', ytitle='Energy (J)', background=vector(0.2, 0.6, 0.2))

i_t = gcurve(color=color.blue, graph=scene1)
v_t = gcurve(color=color.red, graph=scene1)
E_t = gcurve(color=color.red, graph=scene2)

while t <= 12 * T:
    rate(10000)
    V = 36 * sin(2 * pi * fd * t)
    VR = i * R
    VC = Q / C
    VL = V - VC - VR
    i += VL / L * dt
    Q += i * dt
    i_t.plot(pos=(t, i))
    v_t.plot(pos=(t, V / 100))
    E = Q**2 / 2 / C + 1 / 2 * L * i**2
    E_t.plot(pos=(t, E))
    t += dt

    if t >= 9 * T and check == 0:
        i_after = i
        if i_before < i_after:
            i_before = i_after
        else:
            check = 1
            i_get_t = t
            print(f'I magnitude = {i_before}')
            if check == 1 and checkV == 1:
                print(f'phase = {abs(v_get_t - i_get_t) / T * 360}')
        if t >= 9 * T and checkV == 0:
            v_after = V
            if v_before < v_after:
                v_before = v_after
            else:
                checkV = 1
                v_get_t = t
                if check == 1 and checkV == 1:
                    print(f'phase = {abs(v_get_t - i_get_t) / T * 360}')
        E_check = E
        E_time = t

while 12 * T <= t <= 20 * T:
    rate(10000)
    V = 0
    VR = i * R
    VC = Q / C
    VL = V - VC - VR
    i += VL / L * dt
    Q += i * dt
    i_t.plot(pos=(t, i))
    v_t.plot(pos=(t, V / 100))
    E = Q**2 / 2 / C + L * i**2 / 2
    E_t.plot(pos=(t, E))
    t += dt
    if E <= E_check * 0.1 and checkE == 0:
        checkE = 1
        print(f'when t = {t}, decay to 10%. Total time from power off to 10% = {t - E_time}')

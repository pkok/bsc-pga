title "Figure 1"
camrot 0.1 [-2*e1^e2]
bgcolor 0.0 0.0 0.0 0.0
olcolor 0.0 0.0 0.0 0.0
cvcolor white
tsmode text
tsmode bold

factor e3ga 1 [1.00*e1]
factor e3ga 2 [1.00*e2]
factor e3ga 3 [1.00*e3]

fgcolor red
e3ga p [1.5*e1] magnitude
e3ga m [e3] magnitude
e3ga d [e2] magnitude
fgcolor green
c3ga L [1.5*e1^e2^ni-e2^no^ni] orientation

fgcolor black
fontsize 30
label l_p [e1-0.1*e2] "p"
label l_d d "d"
label l_m [e3+0.1*e2] "\eqn{m = p \cp d}"
label l_L [1.5*e1+0.2*e2] "L"

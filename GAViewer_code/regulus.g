batch draw_regulus(line, twoblade, res_trans, res_rot) {
  R = cos(pi / res_rot) - sin(pi / res_rot) twoblade;
  t = dual((e3ga) twoblade);
  T = 1 - res_trans t ni / 2;

  lines[0] = line,
  for (i = 1; i < res_rot; i = i + 1) {
    lines[i] = R lines[i-1] / R,
  }

  for (j = -res_trans; j < res_trans; j = j + 1) {
    plane = c3ga_point(j*t)^twoblade^ni;
    for (i = 0; i < res_rot; i = i + 1) {
      vectors[(j*res_rot) + i] = (e3ga) (no . dual(dual(plane)^dual(lines[i])));
      points[(j*res_rot) + i] = c3ga_point(vectors[j*res_rot + i]),
    }
  }
}

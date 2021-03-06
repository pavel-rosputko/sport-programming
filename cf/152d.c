#include <stdio.h>

typedef struct { int x1, y1, x2, y2; } rect;

char a[1000][1001];
int cc;

int cover(rect r) {
	for (int x = r.x1; x <= r.x2; x++) {
		if (a[x][r.y1] == '.' || a[x][r.y2] == '.')
			return 0;
		if (a[x][r.y1] == '#')
			a[x][r.y1] = '%', cc++;
		if (a[x][r.y2] == '#')
			a[x][r.y2] = '%', cc++;
	}

	for (int y = r.y1; y <= r.y2; y++) {
		if (a[r.x1][y] == '.' || a[r.x2][y] == '.')
			return 0;
		if (a[r.x1][y] == '#')
			a[r.x1][y] = '%', cc++;
		if (a[r.x2][y] == '#')
			a[r.x2][y] = '%', cc++;
	}

	return 1;
}

void print(rect r) {
	printf("%d %d %d %d\n", r.x1+1, r.y1+1, r.x2+1, r.y2+1);
}

void clear(rect r) {
	for (int x = r.x1; x <= r.x2; x++) {
		if (a[x][r.y1] == '%')
		       a[x][r.y1] = '#';
		if (a[x][r.y2] == '%')
		       a[x][r.y2] = '#';
	}

	for (int y = r.y1; y <= r.y2; y++) {
		if (a[r.x1][y] == '%')
		       a[r.x1][y] = '#';
		if (a[r.x2][y] == '%')
		       a[r.x2][y] = '#';
	}
}

int main() {
	int n, m;
	scanf("%d%d", &n, &m);

	int c = 0;
	for (int i = 0; i < n; i++) {
		scanf("%s", a[i]);
		for (int j = 0; j < m; j++)
			if (a[i][j] == '#')
				c++;
	}

	int hn = 0, h[1000], vn = 0, v[1000];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m-2; j++)
			if (a[i][j] == '#' && a[i][j+1] == '#' && a[i][j+2] == '#') {
				h[hn++] = i;
				break;
			}

	for (int j = 0; j < m; j++)
		for (int i = 0; i < n-2; i++)
			if (a[i][j] == '#' && a[i+1][j] == '#' && a[i+2][j] == '#') {
				v[vn++] = j;
				break;
			}

	if (hn > 4) {
		h[2] = h[hn-2]; h[3] = h[hn-1]; hn = 4;
	}

	if (vn > 4) {
		v[2] = v[vn-2]; v[3] = v[vn-1]; vn = 4;
	}
	
	int rects_n = 0;
	rect rects[40];
	for (int i1 = 0; i1 < hn; i1++) for (int i2 = i1; i2 < hn; i2++)
		for (int j1 = 0; j1 < vn; j1++) for (int j2 = j1; j2 < vn; j2++)
			if (h[i2]-h[i1] > 1 && v[j2]-v[j1] > 1) {
				rect r = {h[i1], v[j1], h[i2], v[j2]};
				rects[rects_n++] = r;
			}

	for (int i = 0; i < rects_n; i++)
		for (int j = i; j < rects_n; j++) {
			rect r1 = rects[i], r2 = rects[j];
			cc = 0;
			if (cover(r1) && cover(r2) && cc == c) {
				puts("YES");
				print(r1); print(r2);
				return 0;
			}

			clear(r1); clear(r2);
		}

	puts("NO");
	return 0;
}

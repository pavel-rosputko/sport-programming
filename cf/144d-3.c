#include <stdio.h>
#include <string.h>

int main() {
	int n, m, s;
	scanf("%d%d%d", &n, &m, &s);
	s--;

	int i, li = 0, lv[200000], lw[200000], ln[200000], g[100000];
	memset(g, -1, sizeof(g));
	for (i = 0; i < m; i++) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		u--; v--;

		lv[li] = v; lw[li] = w; ln[li] = g[u]; g[u] = li; li++;
		lv[li] = u; lw[li] = w; ln[li] = g[v]; g[v] = li; li++;
	}

	int u, d[100000];
	for (u = 0; u < n; u++)
		d[u] = 1000000000;
	d[s] = 0;

	char b[100000], bb[100000];
	memset(b, 0, sizeof(b)); // reached
	memset(bb, 0, sizeof(bb)); //  processed
	b[s] = 1;

	const int ql = 200001;
	int qs = 0, qe = 0, q[200001];
	q[qe] = s; qe++;

	while (qs != qe) {
		int u = q[qs]; qs = (qs + 1) % ql;
		bb[u] = 1;

		for (li = g[u]; li != -1; li = ln[li]) {
			int v = lv[li], w = lw[li];

			if (d[u] + w < d[v]) {
				d[v] = d[u] + w;
				if (!b[v]) {
					b[v] = 1;
					q[qe] = v; qe = (qe + 1) % ql;
				} else if (bb[v]) {
					bb[v] = 0;
					qs = (qs - 1 + ql) % ql;
					q[qs] = v;
				}
			}
		}
	}

	int l;
	scanf("%d", &l);

	int c = 0;
	for (u = 0; u < n; u++) {
		if (d[u] == l)
			c++;

		for (li = g[u]; li != -1; li = ln[li]) {
			int v = lv[li], w = lw[li];
			
			if (d[u] < l && l < d[u] + w) {
				int x = l - d[u];
				if (2*x == d[v] - d[u] + w && u < v)
					c++;
				if (2*x < d[v] - d[u] + w)
					c++;
			}
		}
	}

	printf("%d\n", c);

	return 0;
}


def floyd_warshell(n, fares):
    INF = 100000*n
    dist = [[INF for _ in range(n+1)] for _ in range(n+1)]
    for v1, v2, f in fares:
        dist[v1][v2] = f
        dist[v2][v1] = f
    for k in range(1, n+1):
        for i in range(1, n+1):
            for j in range(1, n+1):
                if i == j:
                    dist[i][j] = 0
                else:
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])    
    return dist


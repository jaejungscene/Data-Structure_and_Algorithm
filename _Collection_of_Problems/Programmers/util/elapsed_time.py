import time

def elapsed_time(func):
    def wrapper(*args, **kwargs):
        start = time.time()
        output = func(*args, **kwargs)
        print(f"{func.__name__} elapsed time: {time.time()-start}")
        return output
    return wrapper
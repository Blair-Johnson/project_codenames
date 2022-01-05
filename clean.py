
with open("./adjectives_base.txt", 'r') as f:
    lines = f.readlines()
    clean = []
    for line in lines:
        post_index = line.split('.')[1]
        post_index = post_index.split(' ')
        post_index = [item.strip() for item in post_index]
        if post_index[-1].isdigit():
            post_index.pop(-1)
        post_index.append('\n')
        clean.append(' '.join(post_index))
with open('./adjectives.txt', 'w+') as f:
    for line in clean:
        f.write(line)

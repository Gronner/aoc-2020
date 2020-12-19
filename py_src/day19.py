import regex
import functools

def prepare_input(data):
    rules, data = data.split('\n\n')
    rules = rules.split('\n')
    data = data.split('\n')
    for rule in rules:
        a, b = rule.split(': ')
        parsed_rules[int(a)] = b

    parsed_rules[8] = '42 | 42 8'
    parsed_rules[11] = '42 31 | 42 11 31'

    return parsed_rules, data

parsed_rules = {}
@functools.lru_cache(None)
def recurse_rules(r):
    if r == 8:
        return '(' + recurse_rules(42) + '+' + ')'
    if r == 11:
        return '(?P<Rule11>%s(?P&Rule11)%s|%s%s)' % (recurse_rules(42), recurse_rules(31), recurse_rules(42), recurse_rules(31))
    if '"' in parsed_rules[r]:
        tmp = parsed_rules[r].replace('"', '')
        return '(' + tmp + ')'
    res = []
    for chunk in parsed_rules[r].split(' | '):
        x = ''.join(recurse_rules(int(c)) for c in chunk.split())
        res.append(x)
    return '(' + '|'.join(res) + ')'


def monster_message():
    global parsed_rules

    with open("../data/day19.txt", 'r') as f:
        data = f.read()
    parsed_rules, data = prepare_input(data)
    new_rule  = '^' + recurse_rules(0) + '$'
    count = 0
    for datum in data:
        count += regex.match(new_rule, datum) is not None

    print(count)

if __name__ == "__main__":
    monster_message()


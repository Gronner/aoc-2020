import functools
import regex

PARSED_RULES = {}

def prepare_input(data):
    rules, data = data.split('\n\n')
    rules = rules.split('\n')
    data = data.split('\n')
    for rule in rules:
        rule_id, rule_equation = rule.split(': ')
        PARSED_RULES[int(rule_id)] = rule_equation

    PARSED_RULES[8] = '42 | 42 8'
    PARSED_RULES[11] = '42 31 | 42 11 31'

    return PARSED_RULES, data

@functools.lru_cache(None)
def recurse_rules(r_idx):
    global PARSED_RULES
    if r_idx == 8:
        return '(' + recurse_rules(42) + '+' + ')'
    if r_idx == 11:
        return '(?P<Rule11>%s(?P&Rule11)%s|%s%s)' % (recurse_rules(42),
                                                     recurse_rules(31),
                                                     recurse_rules(42),
                                                     recurse_rules(31))
    if '"' in PARSED_RULES[r_idx]:
        tmp = PARSED_RULES[r_idx].replace('"', '')
        return '(' + tmp + ')'
    res = []
    for side in PARSED_RULES[r_idx].split(' | '):
        tmp = ''.join(recurse_rules(int(c)) for c in side.split())
        res.append(tmp)
    return '(' + '|'.join(res) + ')'


def monster_message():
    global PARSED_RULES

    with open("../data/day19.txt", 'r') as input_file:
        data = input_file.read()
    PARSED_RULES, data = prepare_input(data)
    new_rule = recurse_rules(0)
    count = 0
    for datum in data:
        count += regex.fullmatch(new_rule, datum) is not None

    print(count)

if __name__ == "__main__":
    monster_message()

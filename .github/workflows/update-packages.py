import yaml
import subprocess


def get_latest_git_tag(repository, ignore):
    ignore_commands = 'grep -v {'

    for s in ignore.split(','):
        if s != '':
            ignore_commands += f' | grep -v {s}'

    grep_command = f'git ls-remote --tags {repository}'\
                   " | sort -t '/' -k 3 -k 4 -V"\
                   f' | {ignore_commands}'\
                   " | awk -F/ '{ print $3 }' "\
                   f' | tail -n1'

    output = subprocess.run(grep_command, shell=True, capture_output=True)
    return output.stdout.strip().decode('utf-8')


if __name__ == '__main__':
    with open('packages.yml', 'r') as f:
        packages = yaml.safe_load(f)

    for name, p in packages.items():
        if 'repository' in p:
            p['version'] = get_latest_git_tag(p['repository'], p.get('ignore', ''))

            # remove 'v' prefix when requested
            if not p.get('include_v_prefix', True) and p['version'][0] == 'v':
                p['version'] = p['version'][1:]

    print(yaml.dump(packages))

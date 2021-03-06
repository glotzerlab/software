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
        if 'repository' in p and p['repository'] is not None:
            new_version = get_latest_git_tag(p['repository'],
                                             p.get('ignore', ''))

            # remove 'v' prefix when requested
            if not p.get('include_v_prefix', True) and new_version[0] == 'v':
                new_version = new_version[1:]

            if p['version'] != new_version:
                print(f"Updating {name} {p['version']} -> {new_version}")
                p['version'] = new_version

    with open('packages.yml', 'w') as f:
        yaml.dump(packages, f)

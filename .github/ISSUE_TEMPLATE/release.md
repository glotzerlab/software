---
name: Release checklist
about: '[for maintainer use]'
title: 'Release 2020.XX'
labels: ''
assignees: 'joaander'

---

Release checklist:

- [ ] Update change log.
  - ``git log --format=oneline --first-parent `git log -n 1 --pretty=format:%H -- CHANGELOG.rst`...``
  - [milestone](https://github.com/glotzerlab/software/milestones)
- [ ] Check readthedocs build, especially change log formatting.
  - [Build status](https://readthedocs.org/projects/glotzerlab-software/builds/)
  - [Output](https://glotzerlab-software.readthedocs.io/en/latest/)
- [ ] Tag and push.
- [ ] Build singularity images.
- [ ] Upload singularity images.

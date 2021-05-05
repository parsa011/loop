# Contributing to Loop

When contributing to the Loop programming language, please be sure that the change(s) you wish to make are in line with the project vision. If you are unsure about this, open an issue first, so we can discuss it. If you are already confident that it's a good fit, you can proceed directly to a Pull Request.

Everyone is welcome to work on the project.

## Communication


Discord: [Loop Discord](https://discord.gg/4JRxNKMvtb)

## Issue policy

Please do post any bugs you find, keeping the following in mind:

* One issue per bug. Putting multiple things in the same issue makes both discussion and completion unnecessarily complicated.

## Code submission policy

Nobody is perfect, and sometimes we mess things up. That said, here are some good dos & dont's to try and stick to:

**Do:**

* Write in idiomatic C++17
* Choose expressive variable, function and class names. Make it as obvious as possible what the code is doing.
* Split your changes into separate, atomic commits.
* Make sure your commits are rebased on the master branch.
* Wrap your commit messages at 72 characters.
* The first line of the commit message should have the format "Category: Brief description of what's being changed". The "category" can be a subdirectory, but also something like "POSIX compliance" or "ClassName". Whatever seems logical.
* Write your commit messages in proper English, with care and punctuation.
* Squash your commits when making revisions after a patch review.
  
**Don't:**

* Submit code that's incompatible with the project licence (MIT)
* Iterate excessively on your design across multiple commits.
* Use weasel-words like "refactor" or "fix" to avoid explaining what's being changed.
* Include commented-out code.
* Write in C.
* Attempt large architectural changes until you are familiar with the system and have worked on it for a while.

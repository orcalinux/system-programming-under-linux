# Task 01 README

## Counting Lines in /etc/group

To count the number of lines in the `/etc/group` file, use the following command:

```bash
wc -l /etc/group
```

This command uses the `wc` (word count) command with the `-l` option to count the number of lines in the specified file.

## Prompt Before Every Removal

When referring to the "prompt before every removal," it typically relates to the safety feature in Unix-like operating systems when using the `rm` (remove) command. When you run `rm` without additional options, some systems prompt you to confirm the deletion of files before proceeding. This is a safety measure to prevent accidental data loss.

For example:
```bash
rm file.txt
```
This might prompt:
```
rm: remove regular file 'file.txt'? 
```

## Alias

An alias in a command-line interface is a custom shorthand or substitute for a longer command. It allows users to define their own commands or modify existing ones for convenience. Aliases are usually set in configuration files like `.bashrc` or `.bash_profile`.

## List All Current Aliases

To list all current aliases in the Bash shell, use the following command:

```bash
alias
```

This command displays a list of currently defined aliases.

## Create an Alias for 'rm -i'

To create an alias for 'rm -i' (interactive mode), use the following command:

```bash
alias rmi='rm -i'
```

This alias, named 'rmi,' enables interactive mode for the 'rm' command, prompting for confirmation before removing each file.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <elf.h>

/**
 * close_elf - Close the ELF file.
 * @fd: The file descriptor of the ELF file.
 */
void close_elf(int fd)
{
	if (close(fd) == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close file descriptor\n");
		exit(98);
	}
}

/**
 * check_elf - Check if the file is an ELF file.
 * @e_ident: The ELF identification bytes.
 */
void check_elf(unsigned char *e_ident)
{
	if (e_ident[EI_MAG0] != ELFMAG0 ||
	    e_ident[EI_MAG1] != ELFMAG1 ||
	    e_ident[EI_MAG2] != ELFMAG2 ||
	    e_ident[EI_MAG3] != ELFMAG3)
	{
		dprintf(STDERR_FILENO, "Error: Not an ELF file\n");
		exit(98);
	}
}

/**
 * print_elf_ident - Print the ELF identification bytes.
 * @e_ident: The ELF identification bytes.
 */
void print_elf_ident(unsigned char *e_ident)
{
	int i;

	printf("  Magic:   ");
	for (i = 0; i < EI_NIDENT; i++)
		printf(" %02x", e_ident[i]);
	printf("\n");
}

/**
 * print_type_and_entry - Print the ELF type and entry point address.
 * @e_type: The ELF file type.
 * @e_entry: The entry point address.
 * @e_ident: The ELF identification bytes.
 */
void print_type_and_entry(uint16_t e_type, uint64_t e_entry, unsigned char *e_ident)
{
	const char *type_str;

	if (e_ident[EI_CLASS] == ELFCLASS32)
	{
		type_str = e_type == ET_EXEC ? "EXEC (Executable file)" :
			   e_type == ET_DYN ? "DYN (Shared object file)" :
			   e_type == ET_REL ? "REL (Relocatable file)" :
			   "UNKNOWN";
	}
	else if (e_ident[EI_CLASS] == ELFCLASS64)
	{
		type_str = e_type == ET_EXEC ? "EXEC (Executable file)" :
			   e_type == ET_DYN ? "DYN (Shared object file)" :
			   e_type == ET_REL ? "REL (Relocatable file)" :
			   "UNKNOWN";
	}
	else
	{
		type_str = "UNKNOWN";
	}

	printf("  Type:    %s\n", type_str);
	printf("  Entry point address:               0x%lx\n", e_entry);
}

/**
 * main - Entry point.
 * @argc: The number of command-line arguments.
 * @argv: An array of pointers to the arguments.
 *
 * Return: 0 on success.
 */
int main(int argc, char *argv[])
{
	Elf64_Ehdr *header;
	int fd, r;

	if (argc != 2)
	{
		dprintf(STDERR_FILENO, "Usage: %s <ELF file>\n", argv[0]);
		exit(98);
	}

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't read file %s\n", argv[1]);
		exit(98);
	}

	header = malloc(sizeof(Elf64_Ehdr));
	if (header == NULL)
	{
		close_elf(fd);
		dprintf(STDERR_FILENO, "Error: Can't allocate memory\n");
		exit(98);
	}

	r = read(fd, header, sizeof(Elf64_Ehdr));
	if (r == -1)
	{
		free(header);
		close_elf(fd);
		dprintf(STDERR_FILENO, "Error: Can't read file %s\n", argv[1]);
		exit(98);
	}

	check_elf(header->e_ident);
	printf("ELF Header:\n");
	print_elf_ident(header->e_ident);
	print_type_and_entry(header->e_type, header->e_entry, header->e_ident);

	free(header);
	close_elf(fd);
	return 0;
}

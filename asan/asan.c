const char *
__asan_default_options()
{
	return "strict_string_checks=1:\
		detect_stack_use_after_return=1:\
		check_initialization_order=1:\
		strict_init_order=1:\
		detect_invalid_pointer_pairs=9:\
		halt_on_error=0\
		detect_leaks=1\
		use_unaligned=1";
}

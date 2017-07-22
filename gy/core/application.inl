template <typename _APP_TYPE, typename _ARG_TYPE>
result_t setApplication(int argc, _ARG_TYPE argv)
{
	//GApplication::statusInitializer();

	auto app = std::make_shared<_APP_TYPE>();
	if (false == dynamic_cast<GApplication *>(app.get())) { return GY_FAIL; }

	//app->parsingArgument(argc, argv);

	return startApplication(std::static_pointer_cast<GApplication>(app));
}
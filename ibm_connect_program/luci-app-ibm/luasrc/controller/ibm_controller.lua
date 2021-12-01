module("luci.controller.ibm_controller", package.seeall)

function index()
	entry({"admin", "services", "ibm"}, cbi("ibm_model"), _("ibm_program"),105)
end

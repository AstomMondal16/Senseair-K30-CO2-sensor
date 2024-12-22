set(component_srcs "k30.c")

idf_component_register(SRCS "${component_srcs}" PRIV_REQUIRES driver INCLUDE_DIRS "include")




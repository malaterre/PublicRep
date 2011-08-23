#ifndef ASPELL_HPP_
#define ASPELL_HPP_

// This file has been generated automatically

#include "FunTraits.h"
#include "DynFunctor.h"
#include "aspell.h"

#define SYM(x) extern const char nm_##x[];

SYM(delete_aspell_filter);
REGISTER_TYPEOF(void (AspellFilter *), 4);

SYM(aspell_reset_cache);
REGISTER_TYPEOF(int (const char *), 5);

SYM(aspell_string_list_remove);
REGISTER_TYPEOF(int (AspellStringList *, const char *), 11);

SYM(aspell_key_info_enumeration_clone);
REGISTER_TYPEOF(AspellKeyInfoEnumeration * (const AspellKeyInfoEnumeration *), 14);

SYM(aspell_module_info_enumeration_assign);
REGISTER_TYPEOF(void (AspellModuleInfoEnumeration *, const AspellModuleInfoEnumeration *), 16);

SYM(aspell_document_checker_error_message);
REGISTER_TYPEOF(const char * (const AspellDocumentChecker *), 17);

SYM(aspell_speller_session_word_list);
REGISTER_TYPEOF(const AspellWordList * (AspellSpeller *), 19);

SYM(aspell_dict_info_enumeration_at_end);
REGISTER_TYPEOF(int (const AspellDictInfoEnumeration *), 23);

SYM(aspell_string_enumeration_at_end);
REGISTER_TYPEOF(int (const AspellStringEnumeration *), 24);

SYM(aspell_speller_check);
REGISTER_TYPEOF(int (AspellSpeller *, const char *, int), 32);

SYM(aspell_speller_error_number);
REGISTER_TYPEOF(unsigned int (const AspellSpeller *), 33);

SYM(get_aspell_dict_info_list);
REGISTER_TYPEOF(AspellDictInfoList * (AspellConfig *), 34);

SYM(aspell_string_map_to_mutable_container);
REGISTER_TYPEOF(AspellMutableContainer * (AspellStringMap *), 41);

SYM(aspell_word_list_elements);
REGISTER_TYPEOF(AspellStringEnumeration * (const AspellWordList *), 43);

SYM(aspell_config_keyinfo);
REGISTER_TYPEOF(const AspellKeyInfo * (AspellConfig *, const char *), 47);

SYM(aspell_config_possible_elements);
REGISTER_TYPEOF(AspellKeyInfoEnumeration * (AspellConfig *, int), 52);

SYM(aspell_config_error);
REGISTER_TYPEOF(const AspellError * (const AspellConfig *), 53);

SYM(to_aspell_document_checker);
REGISTER_TYPEOF(AspellDocumentChecker * (AspellCanHaveError *), 57);

SYM(aspell_key_info_enumeration_next);
REGISTER_TYPEOF(const AspellKeyInfo * (AspellKeyInfoEnumeration *), 61);

SYM(new_aspell_config);
REGISTER_TYPEOF(AspellConfig * (), 62);

SYM(delete_aspell_config);
REGISTER_TYPEOF(void (AspellConfig *), 63);

SYM(aspell_document_checker_error_number);
REGISTER_TYPEOF(unsigned int (const AspellDocumentChecker *), 64);

SYM(delete_aspell_string_enumeration);
REGISTER_TYPEOF(void (AspellStringEnumeration *), 66);

SYM(aspell_string_pair_enumeration_at_end);
REGISTER_TYPEOF(int (const AspellStringPairEnumeration *), 69);

SYM(delete_aspell_can_have_error);
REGISTER_TYPEOF(void (AspellCanHaveError *), 72);

SYM(aspell_speller_add_to_session);
//REGISTER_TYPEOF(int (AspellSpeller *, const char *, int), 73);

SYM(aspell_module_info_enumeration_next);
REGISTER_TYPEOF(const AspellModuleInfo * (AspellModuleInfoEnumeration *), 81);

SYM(aspell_string_list_clone);
REGISTER_TYPEOF(AspellStringList * (const AspellStringList *), 82);

SYM(aspell_document_checker_next_misspelling);
REGISTER_TYPEOF(AspellToken (AspellDocumentChecker *), 83);

SYM(aspell_string_enumeration_clone);
REGISTER_TYPEOF(AspellStringEnumeration * (const AspellStringEnumeration *), 84);

SYM(aspell_string_map_elements);
REGISTER_TYPEOF(AspellStringPairEnumeration * (const AspellStringMap *), 85);

SYM(aspell_string_map_assign);
REGISTER_TYPEOF(void (AspellStringMap *, const AspellStringMap *), 87);

SYM(aspell_document_checker_reset);
REGISTER_TYPEOF(void (AspellDocumentChecker *), 89);

SYM(aspell_mutable_container_remove);
REGISTER_TYPEOF(int (AspellMutableContainer *, const char *), 92);

SYM(aspell_filter_error_number);
REGISTER_TYPEOF(unsigned int (const AspellFilter *), 93);

SYM(aspell_config_clone);
REGISTER_TYPEOF(AspellConfig * (const AspellConfig *), 94);

SYM(aspell_string_pair_enumeration_next);
REGISTER_TYPEOF(AspellStringPair (AspellStringPairEnumeration *), 97);

SYM(aspell_speller_store_replacement);
REGISTER_TYPEOF(int (AspellSpeller *, const char *, int, const char *, int), 98);

SYM(delete_aspell_string_pair_enumeration);
REGISTER_TYPEOF(void (AspellStringPairEnumeration *), 100);

SYM(aspell_speller_save_all_word_lists);
REGISTER_TYPEOF(int (AspellSpeller *), 101);

SYM(aspell_dict_info_enumeration_assign);
REGISTER_TYPEOF(void (AspellDictInfoEnumeration *, const AspellDictInfoEnumeration *), 104);

SYM(aspell_string_map_insert);
REGISTER_TYPEOF(int (AspellStringMap *, const char *, const char *), 109);

SYM(aspell_module_info_list_elements);
REGISTER_TYPEOF(AspellModuleInfoEnumeration * (const AspellModuleInfoList *), 113);

SYM(delete_aspell_string_list);
REGISTER_TYPEOF(void (AspellStringList *), 114);

SYM(aspell_string_map_clone);
REGISTER_TYPEOF(AspellStringMap * (const AspellStringMap *), 115);

SYM(aspell_document_checker_process);
REGISTER_TYPEOF(void (AspellDocumentChecker *, const char *, int), 117);

SYM(aspell_config_error_message);
REGISTER_TYPEOF(const char * (const AspellConfig *), 118);

SYM(delete_aspell_string_map);
REGISTER_TYPEOF(void (AspellStringMap *), 120);

SYM(aspell_string_map_replace);
//REGISTER_TYPEOF(int (AspellStringMap *, const char *, const char *), 121);

SYM(aspell_config_elements);
REGISTER_TYPEOF(AspellStringPairEnumeration * (AspellConfig *), 122);

SYM(aspell_string_enumeration_next);
REGISTER_TYPEOF(const char * (AspellStringEnumeration *), 124);

SYM(aspell_speller_main_word_list);
//REGISTER_TYPEOF(const AspellWordList * (AspellSpeller *), 125);

SYM(to_aspell_speller);
REGISTER_TYPEOF(AspellSpeller * (AspellCanHaveError *), 126);

SYM(aspell_document_checker_filter);
REGISTER_TYPEOF(AspellFilter * (AspellDocumentChecker *), 127);

SYM(aspell_string_map_size);
REGISTER_TYPEOF(unsigned int (const AspellStringMap *), 128);

SYM(new_aspell_string_map);
REGISTER_TYPEOF(AspellStringMap * (), 129);

SYM(aspell_string_list_clear);
//REGISTER_TYPEOF(void (AspellStringList *), 130);

SYM(new_aspell_speller);
REGISTER_TYPEOF(AspellCanHaveError * (AspellConfig *), 135);

SYM(aspell_string_map_remove);
REGISTER_TYPEOF(int (AspellStringMap *, const char *), 138);

SYM(aspell_config_retrieve_list);
REGISTER_TYPEOF(int (AspellConfig *, const char *, AspellMutableContainer *), 139);

SYM(aspell_dict_info_list_size);
REGISTER_TYPEOF(unsigned int (const AspellDictInfoList *), 140);

SYM(new_aspell_document_checker);
REGISTER_TYPEOF(AspellCanHaveError * (AspellSpeller *), 144);

SYM(aspell_string_pair_enumeration_clone);
REGISTER_TYPEOF(AspellStringPairEnumeration * (const AspellStringPairEnumeration *), 151);

SYM(aspell_string_pair_enumeration_assign);
REGISTER_TYPEOF(void (AspellStringPairEnumeration *, const AspellStringPairEnumeration *), 152);

SYM(new_aspell_string_list);
REGISTER_TYPEOF(AspellStringList * (), 153);

SYM(aspell_config_set_extra);
REGISTER_TYPEOF(void (AspellConfig *, const AspellKeyInfo *, const AspellKeyInfo *), 154);

SYM(aspell_key_info_enumeration_at_end);
REGISTER_TYPEOF(int (const AspellKeyInfoEnumeration *), 155);

SYM(aspell_error_is_a);
REGISTER_TYPEOF(int (const AspellError *, const AspellErrorInfo *), 156);

SYM(aspell_config_retrieve_bool);
REGISTER_TYPEOF(int (AspellConfig *, const char *), 157);

SYM(aspell_config_have);
REGISTER_TYPEOF(int (const AspellConfig *, const char *), 159);

SYM(aspell_filter_error_message);
REGISTER_TYPEOF(const char * (const AspellFilter *), 163);

SYM(aspell_speller_error_message);
REGISTER_TYPEOF(const char * (const AspellSpeller *), 167);

SYM(aspell_string_map_clear);
//REGISTER_TYPEOF(void (AspellStringMap *), 168);

SYM(aspell_dict_info_enumeration_next);
REGISTER_TYPEOF(const AspellDictInfo * (AspellDictInfoEnumeration *), 169);

SYM(aspell_filter_error);
REGISTER_TYPEOF(const AspellError * (const AspellFilter *), 170);

SYM(aspell_error_number);
REGISTER_TYPEOF(unsigned int (const AspellCanHaveError *), 171);

SYM(aspell_string_map_add);
//REGISTER_TYPEOF(int (AspellStringMap *, const char *), 172);

SYM(aspell_config_replace);
REGISTER_TYPEOF(int (AspellConfig *, const char *, const char *), 174);

SYM(aspell_document_checker_error);
REGISTER_TYPEOF(const AspellError * (const AspellDocumentChecker *), 175);

SYM(aspell_mutable_container_to_mutable_container);
REGISTER_TYPEOF(AspellMutableContainer * (AspellMutableContainer *), 176);

SYM(aspell_error_message);
REGISTER_TYPEOF(const char * (const AspellCanHaveError *), 178);

SYM(aspell_config_remove);
//REGISTER_TYPEOF(int (AspellConfig *, const char *), 179);

SYM(aspell_config_assign);
REGISTER_TYPEOF(void (AspellConfig *, const AspellConfig *), 180);

SYM(aspell_config_retrieve);
REGISTER_TYPEOF(const char * (AspellConfig *, const char *), 182);

SYM(aspell_error);
REGISTER_TYPEOF(const AspellError * (const AspellCanHaveError *), 183);

SYM(aspell_module_info_enumeration_clone);
REGISTER_TYPEOF(AspellModuleInfoEnumeration * (const AspellModuleInfoEnumeration *), 184);

SYM(aspell_dict_info_enumeration_clone);
REGISTER_TYPEOF(AspellDictInfoEnumeration * (const AspellDictInfoEnumeration *), 185);

SYM(aspell_config_error_number);
REGISTER_TYPEOF(unsigned int (const AspellConfig *), 186);

SYM(aspell_speller_error);
REGISTER_TYPEOF(const AspellError * (const AspellSpeller *), 187);

SYM(delete_aspell_document_checker);
//REGISTER_TYPEOF(void (AspellDocumentChecker *), 190);

SYM(aspell_string_list_empty);
REGISTER_TYPEOF(int (const AspellStringList *), 191);

SYM(aspell_mutable_container_add);
//REGISTER_TYPEOF(int (AspellMutableContainer *, const char *), 192);

SYM(aspell_module_info_enumeration_at_end);
REGISTER_TYPEOF(int (const AspellModuleInfoEnumeration *), 193);

SYM(aspell_word_list_size);
REGISTER_TYPEOF(unsigned int (const AspellWordList *), 195);

SYM(aspell_string_list_assign);
REGISTER_TYPEOF(void (AspellStringList *, const AspellStringList *), 199);

SYM(aspell_module_info_list_empty);
REGISTER_TYPEOF(int (const AspellModuleInfoList *), 200);

SYM(aspell_string_map_lookup);
REGISTER_TYPEOF(const char * (const AspellStringMap *, const char *), 201);

SYM(aspell_mutable_container_clear);
REGISTER_TYPEOF(void (AspellMutableContainer *), 204);

SYM(to_aspell_filter);
REGISTER_TYPEOF(AspellFilter * (AspellCanHaveError *), 207);

SYM(aspell_string_list_elements);
REGISTER_TYPEOF(AspellStringEnumeration * (const AspellStringList *), 208);

SYM(aspell_config_get_default);
//REGISTER_TYPEOF(const char * (AspellConfig *, const char *), 209);

SYM(aspell_key_info_enumeration_assign);
REGISTER_TYPEOF(void (AspellKeyInfoEnumeration *, const AspellKeyInfoEnumeration *), 212);

SYM(aspell_string_enumeration_assign);
REGISTER_TYPEOF(void (AspellStringEnumeration *, const AspellStringEnumeration *), 213);

SYM(aspell_word_list_empty);
REGISTER_TYPEOF(int (const AspellWordList *), 218);

SYM(delete_aspell_speller);
REGISTER_TYPEOF(void (AspellSpeller *), 219);

SYM(delete_aspell_key_info_enumeration);
REGISTER_TYPEOF(void (AspellKeyInfoEnumeration *), 222);

SYM(aspell_string_list_size);
REGISTER_TYPEOF(unsigned int (const AspellStringList *), 223);

SYM(aspell_string_list_add);
//REGISTER_TYPEOF(int (AspellStringList *, const char *), 224);

SYM(aspell_speller_personal_word_list);
//REGISTER_TYPEOF(const AspellWordList * (AspellSpeller *), 225);

SYM(aspell_string_list_to_mutable_container);
REGISTER_TYPEOF(AspellMutableContainer * (AspellStringList *), 226);

SYM(aspell_string_map_empty);
REGISTER_TYPEOF(int (const AspellStringMap *), 227);

SYM(delete_aspell_dict_info_enumeration);
REGISTER_TYPEOF(void (AspellDictInfoEnumeration *), 228);

SYM(aspell_dict_info_list_empty);
REGISTER_TYPEOF(int (const AspellDictInfoList *), 241);

SYM(aspell_speller_suggest);
REGISTER_TYPEOF(const AspellWordList * (AspellSpeller *, const char *, int), 242);

SYM(delete_aspell_module_info_enumeration);
REGISTER_TYPEOF(void (AspellModuleInfoEnumeration *), 243);

SYM(aspell_module_info_list_size);
REGISTER_TYPEOF(unsigned int (const AspellModuleInfoList *), 244);

SYM(get_aspell_module_info_list);
REGISTER_TYPEOF(AspellModuleInfoList * (AspellConfig *), 246);

SYM(aspell_dict_info_list_elements);
REGISTER_TYPEOF(AspellDictInfoEnumeration * (const AspellDictInfoList *), 247);

SYM(aspell_speller_add_to_personal);
//REGISTER_TYPEOF(int (AspellSpeller *, const char *, int), 248);

SYM(aspell_speller_config);
REGISTER_TYPEOF(AspellConfig * (AspellSpeller *), 249);

SYM(aspell_config_retrieve_int);
//REGISTER_TYPEOF(int (AspellConfig *, const char *), 253);

SYM(aspell_speller_clear_session);
//REGISTER_TYPEOF(int (AspellSpeller *), 255);

#undef SYM

#endif // ASPELL_HPP_
